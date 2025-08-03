#include "minishell.h"
static int      open_all_pipes(int **fd, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (pipe(fd[i]) == -1)
            return (1);
        i++;
    }
    return (0);
}

static void     close_child_fds(int **fd, int pipe_count, int read_index, int write_index)
{
    int j;

    j = 0;
    while (j < pipe_count)
    {
        if (j != read_index)
            close(fd[j][0]);
        if (j != write_index)
            close(fd[j][1]);
        j++;
    }
}

static void execute_pipe_builds(t_minishell *minishell, char **cmd)
{
	if (!ft_strcmp(cmd[0], "env"))
		minishell->exit_status = ft_env(minishell);
	else if (!ft_strcmp(cmd[0], "pwd"))
		minishell->exit_status = ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
		minishell->exit_status = process_for_echo(&minishell->token_list);
	else if (!ft_strcmp(cmd[0], "export"))
		minishell->exit_status = ft_export(minishell);
	else if (!ft_strcmp(cmd[0], "cd"))
		minishell->exit_status = ft_cd(minishell);
	else if (!ft_strcmp(cmd[0], "unset"))
		minishell->exit_status = ft_unset(minishell, *cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		minishell->exit_status = ft_exit(minishell);
	exit(minishell->exit_status);
}
void execute_pipe_child(t_minishell *minishell)
{
	char **cmd;
	char *path;

	if (has_redirect_or_heredoc(minishell))
	{
		minishell->exit_status = handle_redirect(minishell, &minishell->token_list);
		exit(minishell->exit_status);
	}
	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "exit"))
		execute_pipe_builds(minishell, cmd);
	else
	{
		path = get_path(minishell->envp, cmd[0]);
		if (!path)
		{
        	write(2, "minishell: ", 11);
        	write(2, cmd[0], ft_strlen(cmd[0]));
        	write(2, ": command not found\n", 20);
			minishell->exit_status = 127;
		}
		cmd = ft_same_tokens(&minishell->token_list);
		minishell->exit_status = execve(path, cmd, make_env_array(minishell));
		if (minishell->exit_status == -1)
		{
			perror("minishell");
			minishell->exit_status = 126;
		}
		free(path);
		exit(minishell->exit_status);
	}
}

static void	setup_pipe_and_fork(t_minishell *minishell, int i, pid_t *pids, int **fd)
{
    if (i < minishell->count->pipe_count)
        pipe(fd[i]);
    pids[i] = fork();
    if (pids[i] == 0)
    {
        set_default_signals();
        int read_index = -1;
        if (i > 0 && !has_input_redirect_or_heredoc(minishell))
        {
            dup2(fd[i - 1][0], STDIN_FILENO);
            read_index = i - 1;
        }
        if (i < minishell->count->pipe_count)
			dup2(fd[i][1], STDOUT_FILENO);
		close_child_fds(fd, minishell->count->pipe_count, read_index, i);
        execute_pipe_child(minishell);
    }
}

void	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
    int				i;
	int				saved_stdin;
    t_token_list	*tmp;

    i = 0;
    tmp = minishell->token_list;
    while (i < minishell->count->pipe_count + 1)
    {
        minishell->token_list = tmp;
		saved_stdin = dup(STDIN_FILENO);
		if (handle_heredoc(minishell))
        {
            dup2(saved_stdin, STDIN_FILENO);
            close(saved_stdin);
            break ;
        }
        setup_pipe_and_fork(minishell, i, pids, fd);
		dup2(saved_stdin, STDIN_FILENO);
        close(saved_stdin);
		if (i > 0)
            close(fd[i - 1][0]);
        if (i < minishell->count->pipe_count)
            close(fd[i][1]);
        if (tmp)
        {
            while (tmp && tmp->token->type != TOKEN_PIPE)
                tmp = tmp->next;
            if (tmp && tmp->token->type == TOKEN_PIPE)
            {    
				tmp = tmp->next;
				if (!tmp)
				{
					minishell->token_list = NULL;
					perror("minishell");
					break ;
				}
			}
        }
        i++;
    }
}

int	execute_pipe_line(t_minishell *minishell, int i)
{
	int		**fd;
	pid_t	*pids;
	int		status;

	status = 0;
	minishell->exit_status = malloc_fd_and_pid(&fd, &pids, minishell);
	if (minishell->exit_status)
		return (1);
	if (open_all_pipes(fd, minishell->count->pipe_count))
        return (1);
	set_ignore_signals();
	processor(minishell, pids, fd);
	while (i < minishell->count->pipe_count)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < minishell->count->pipe_count + 1)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
        	minishell->exit_status = WEXITSTATUS(status);
		i++;
	}
    i = 0;
    while (i < minishell->count->pipe_count)
        free(fd[i++]);
    free(fd);
    free(pids);
	return (0);
}

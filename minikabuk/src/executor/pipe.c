#include "minishell.h"

int execute_pipe_child(t_minishell *minishell)
{
	char **cmd;
	char *path;

	//if (has_redirect_or_heredoc(minishell))
		//	handle_redirect_or_heredoc(minishell, &tmp);
	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "env"))
		exit(ft_env(minishell));
	else if (!ft_strcmp(cmd[0], "pwd"))
		exit(ft_pwd());
	else if (!ft_strcmp(cmd[0], "echo"))
		exit(process_for_echo(&minishell->token_list));
	else
	{
		path = get_path(minishell->envp, cmd[0]);
		if (!path)
		{
			printf("minishell: %s: command not found\n", cmd[0]);
			return (127);
		}
		if (execve(path, cmd, make_env_array(minishell)) == -1)
		{
			perror("minishell");
			exit(126);
		}
		else
			exit(0);
	}
}

static void	setup_pipe_and_fork(t_minishell *minishell, int i, pid_t *pids, int **fd)
{
    char	**cmd;

    cmd = current_token(minishell->token_list);
    if (i < minishell->count->pipe_count)
        pipe(fd[i % 2]);
    pids[i] = fork();
    if (pids[i] == 0 && !(!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit")))
    {
        set_default_signals();
        if (i > 0)
        {
            dup2(fd[(i - 1) % 2][0], STDIN_FILENO);
            close(fd[(i - 1) % 2][1]);
        }
        if (i < minishell->count->pipe_count)
        {
            dup2(fd[i % 2][1], STDOUT_FILENO);
            close(fd[i % 2][0]);
        }
        execute_pipe_child(minishell);
    }
    else if (pids[i] > 0)
    {
        if (!ft_strcmp(cmd[0], "cd") || !ft_strcmp(cmd[0], "export")
            || !ft_strcmp(cmd[0], "unset") || !ft_strcmp(cmd[0], "exit"))
            execute_in_parent(cmd[0], minishell);
    }
}

void	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
    int				i;
    t_token_list	*tmp;

    i = 0;
    tmp = minishell->token_list;
    while (i < minishell->count->pipe_count + 1)
    {
        minishell->token_list = tmp;
        setup_pipe_and_fork(minishell, i, pids, fd);
        if (tmp)
        {
            while (tmp && tmp->token->type != TOKEN_PIPE)
                tmp = tmp->next;
            if (tmp && tmp->token->type == TOKEN_PIPE)
                tmp = tmp->next;
        }
        i++;
    }
}

int	execute_pipe_line(t_minishell *minishell, int i)
{
	int		**fd;
	pid_t	*pids;

	malloc_fd_and_pid(&fd, &pids, minishell);
	if (!fd || !pids)
		return (1);
	set_ignore_signals();
	processor(minishell, pids, fd);
	while (i < minishell->count->pipe_count)
	{
		close(fd[i % 2][0]);
		close(fd[i % 2][1]);
		i++;
	}
	i = 0;
	while (i < minishell->count->pipe_count + 1)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
    free(fd[0]);
    free(fd[1]);
    free(fd);
	return (0);
}

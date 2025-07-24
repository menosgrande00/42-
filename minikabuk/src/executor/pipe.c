#include "minishell.h"





void	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
    int				i;
    t_token_list	*tmp;

    i = 0;
    tmp = minishell->token_list;
    
    // Create all pipes first
    while (i < minishell->count->pipe_count)
    {
        pipe(fd[i]);
        i++;
    }
    
    i = 0;
    while (i < minishell->count->pipe_count + 1)
    {
        minishell->token_list = tmp;
        
        pids[i] = fork();
        if (pids[i] == 0)
        {
            // Child process
            char **cmd;
            t_token_list *cmd_tmp = tmp;
            
            cmd = ft_same_tokens(&cmd_tmp);
            
            // Set up pipes for child
            if (i > 0)
                dup2(fd[i-1][0], STDIN_FILENO);
            if (i < minishell->count->pipe_count)
                dup2(fd[i][1], STDOUT_FILENO);
                
            // Close all pipe fds in child
            int j = 0;
            while (j < minishell->count->pipe_count)
            {
                close(fd[j][0]);
                close(fd[j][1]);
                j++;
            }
            
            // Execute command
            set_default_signals();
            if (!ft_strcmp(cmd[0], "env"))
                exit(ft_env(minishell));
            else if (!ft_strcmp(cmd[0], "pwd"))
                exit(ft_pwd());
            else if (!ft_strcmp(cmd[0], "echo"))
                exit(process_for_echo(&minishell->token_list));
            else
            {
                char *path = get_path(minishell->envp, cmd[0]);
                if (!path)
                {
                    printf("minishell: %s: command not found\n", cmd[0]);
                    exit(127);
                }
                if (execve(path, cmd, make_env_array(minishell)) == -1)
                {
                    perror("minishell");
                    exit(126);
                }
                free(path);
                exit(0);
            }
        }
        
        // Move to next command
        if (tmp)
        {
            while (tmp && tmp->token->type != TOKEN_PIPE)
                tmp = tmp->next;
            if (tmp && tmp->token->type == TOKEN_PIPE)
                tmp = tmp->next;
        }
        i++;
    }
    
    // Close all pipe fds in parent
    i = 0;
    while (i < minishell->count->pipe_count)
    {
        close(fd[i][0]);
        close(fd[i][1]);
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
	set_ignore_signals();
	processor(minishell, pids, fd);
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

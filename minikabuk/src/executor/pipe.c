#include "minishell.h"

static int execute_pipe_child(t_minishell *minishell)
{
	char **cmd;
	char *path;

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
			ft_printf("minishell: %s: command not found\n", cmd[0]);
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

void	processor(t_minishell *minishell, pid_t *pids, int **fd)
{
	int	i;

	i = 0;
	while (i < minishell->count->pipe_count + 1)
	{
		if (i < minishell->count->pipe_count)
			pipe(fd[i % 2]);
		pids[i] = fork();
		if (pids[i] == 0)
		{
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
		i++;
	}
}

int	execute_pipe_line(t_minishell *minishell, int i)
{
	int	**fd;
	pid_t *pids;

	malloc_fd_and_pid(&fd, &pids, minishell);
	if (!fd || !pids)
		return (1);
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

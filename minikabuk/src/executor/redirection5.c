#include "minishell.h"

static char	*find_command_path(t_env *envp, char **cmd)
{
	char	*path;

	path = get_path(envp, cmd[0]);
	if (!path && is_dot(cmd))
	{
		if (access(cmd[0], F_OK) == 0)
			path = ft_strdup(cmd[0]);
	}
	return (path);
}

static void	child_process_execution(char *path, char **cmd, t_minishell *minishell)
{
	if (execve(path, cmd, make_env_array(minishell)) == -1)
	{
		perror("minishell");
		minishell->exit_status = 126;
		exit(minishell->exit_status);
	}
}

static int	parent_process_wait(pid_t pid, t_minishell *minishell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	minishell->exit_status = 1;
	return (minishell->exit_status);
}

int	execute_external_command(char **cmd, t_minishell *minishell)
{
	char	*path;
	pid_t	pid;

	path = find_command_path(minishell->envp, cmd);
	validate_and_execute(minishell, cmd, path);
	pid = fork();
	if (pid == 0)
		child_process_execution(path, cmd, minishell);
	else if (pid > 0)
		return (parent_process_wait(pid, minishell));
	else
	{
		perror("fork");
		minishell->exit_status = 1;
	}
	return (minishell->exit_status);
}

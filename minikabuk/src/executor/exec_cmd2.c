#include "minishell.h"

void	validate_and_execute(t_minishell *minishell, char **cmd, char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && is_dot(cmd))
	{
		if (S_ISDIR(st.st_mode))
		{
			free(path);
			exit(report_is_a_directory(minishell, cmd[0]));
		}
		else if (!(st.st_mode & S_IXUSR))
		{
			free(path);
			exit(report_perm_denied(minishell, cmd[0]));
		}
	}
	else if (is_dot(cmd))
	{
		free(path);
		exit(report_no_such_file(minishell, cmd[0]));
	}
	if (!path)
		exit(report_cmd_not_found(minishell, cmd[0]));
	execve(path, cmd, make_env_array(minishell));
	exit(1);
}

static void	execute_child_process(t_minishell *minishell, char **cmd, t_token_list **tmp)
{
	char	*path;

	set_default_signals();
	if (!has_redirect_or_heredoc(minishell) && 
		(!ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "pwd") ||
		!ft_strcmp(cmd[0], "echo")))
	{
		minishell->exit_status = exec_child(cmd, minishell);
		exit(minishell->exit_status);
	}
	path = get_path(minishell->envp, cmd[0]);
	if (!path && is_dot(cmd))
	{
		if (access(cmd[0], F_OK) == 0)
			path = ft_strdup(cmd[0]);
	}
	cmd = ft_same_tokens(tmp);
	validate_and_execute(minishell, cmd, path);
}

int	handle_fork_and_execute(t_minishell *minishell, char **cmd, t_token_list *tmp)
{
	pid_t	pid;
	int		status;

	set_ignore_signals();
	pid = fork();
	if (pid == 0 && minishell->token_list->token->type == TOKEN_COMMAND)
		execute_child_process(minishell, cmd, &tmp);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->exit_status = WEXITSTATUS(status);
	else
		minishell->exit_status = 1;
	init_signal();
	return (0);
}

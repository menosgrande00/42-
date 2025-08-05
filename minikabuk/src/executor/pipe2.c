#include "minishell.h"

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

int	execute_pipe_builts(t_minishell *minishell)
{
	char **cmd;

	cmd = current_token(minishell->token_list);
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(*cmd);
	else if(!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	else if(!ft_strcmp(cmd[0], "env"))
		ft_env(minishell);
	return (1);
}

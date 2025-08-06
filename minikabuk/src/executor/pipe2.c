#include "minishell.h"

void execute_pipe_child(t_minishell *minishell)
{
	char	**cmd;
	char	*path;
	char	**env_array;

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
        	report_cmd_not_found(minishell, cmd[0]);
			free_double(cmd);
			exit(127);
		}
		free_double(cmd);
		cmd = ft_same_tokens(&minishell->token_list);
		env_array = make_env_array(minishell);
		minishell->exit_status = execve(path, cmd, env_array);
		free(path);
		exit(minishell->exit_status);
		free_double(cmd);
        free_double(env_array);
        exit(126);
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
	free_double(cmd);
	return (1);
}

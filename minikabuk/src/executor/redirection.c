#include "minishell.h"

void	free_cmd_path(char **cmd_path, int i)
{
	while (cmd_path[i])
	{
		free(cmd_path[i]);
		i++;
	}
	free(cmd_path);
}

char	*get_path(t_env *envp, char *cmd)
{
	char	**paths;
	char	*path;
	t_env	*tmp_env;
	int		i;

	i = 0;
	tmp_env = envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "PATH"))
		{
			paths = ft_split(tmp_env->value, ':');
			if (!paths)
				return (NULL);
			while (paths[i])
			{
				path = ft_strjoin(paths[i], "/");
				path = ft_strjoin(path, cmd);
				if (access(path, X_OK) == 0)
				{
					free_cmd_path(paths, i);
					return (path);
				}
				i++;
			}
			free_cmd_path(paths, i);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*process_env(t_minishell *minishell, char *cmd, char **cmd_path)
{
	t_env	*tmp_env;

	tmp_env = minishell->envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, cmd))
		{
			*cmd_path = get_path(minishell->envp, cmd);
			return (tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
	if (!tmp_env)
		ft_printf("minishell: %s: No such file or directory\n", cmd);
	return (NULL);
}

void	handle_redirect_or_heredoc(t_minishell *minishell, t_token_list **tmp, char **cmd)
{
	char	*env_value;
	char	*cmd_path;

	if ((*tmp)->token->type == TOKEN_COMMAND)
	{
		if (!ft_strcmp((*tmp)->token->value, "echo"))
		{
			if (process_for_echo(tmp))
			{
				ft_printf("minishell: memory allocation error\n");
				return ;
			}
		}
		else if (!ft_strcmp((*tmp)->token->value, "pwd"))
			ft_pwd();
		else if (!ft_strcmp((*tmp)->token->value, "env"))
			ft_env(minishell);
		else
		{
			env_value = process_env(minishell, cmd[0], &cmd_path);
			if (env_value && cmd_path)
			{
				cmd[0] = env_value;
				if (execve(cmd_path, cmd, make_env_array(minishell)) == -1)
                {
                    perror("minishell");
                    free(cmd_path);
                    exit(1);
                }
			}
			else
			{
				ft_printf("minishell: No such file or directory\n");
				exit(1);
			}
		}
	}
}

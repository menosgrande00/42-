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
	char	*temp_path;
	t_env	*tmp_env;
	int		i;

	i = -1;
	tmp_env = envp;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "PATH="))
		{
			paths = ft_split(tmp_env->value, ':');
			if (!paths)
				return (NULL);
			while (paths[++i])
			{
				temp_path = ft_strjoin(paths[i], "/");
				path = ft_strjoin(temp_path, cmd);
				free(temp_path);
				if (access(path, X_OK) == 0)
				{
					free_cmd_path(paths, 0);
					return (path);
				}
				free(path);
			}
			free_cmd_path(paths, 0);
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
		if (!ft_strncmp(tmp_env->key, cmd, ft_strlen(tmp_env->key) - 1))
		{
			*cmd_path = get_path(minishell->envp, cmd);
			return (tmp_env->value);
		}
		tmp_env = tmp_env->next;
	}
	if (!tmp_env)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
	}
	return (NULL);
}

#include "minishell.h"

static char	*ft_token_with_spaces(t_minishell *minishell)
{
	char	*input;
	int		i;

	i = ft_strlen(minishell->input);
	input = ft_strdup(ft_strnstr(minishell->input, "cd", i) + 2);
	i = 0;

	while (*input == ' ' || *input == '\t')
		input++;
	return (input);
}

static char	*find_home(t_minishell *minishell)
{
	char	*home;
	t_env	*env;

	home = NULL;
	env = minishell->envp;
	while (env)
	{
		if (ft_strncmp(env->key, "HOME", ft_strlen(env->key) - 1) == 0)
		{
			home = env->value;
			break;
		}
		env = env->next;
	}
	return (home);
}

static int	ft_cd_back_one(char *cwd, char *new_path, t_minishell *minishell)
{
	int		i;
	char	**paths;
	char	*home;

	i = 0;
	paths = ft_split(cwd, '/');
	home = find_home(minishell);
	new_path = ft_strdup("");
	if (!home)
	{
		report_error(minishell, "minishell: cd: HOME not set\n", 1);
		free(cwd);
		return (1);
	}
	if (!ft_strcmp(cwd, home))
		return (1);
	while (paths[i + 1])
	{
		new_path = ft_strjoin(new_path, "/");
		new_path = ft_strjoin(new_path, paths[i]);
		i++;
	}
	free(cwd);
	if (!new_path)
		return (1);
	if (chdir(new_path))
	{
		report_no_such_file(minishell, new_path);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

static int	ft_go_path(char *cwd, char *new_path, char *current_token)
{
	free(cwd);
	new_path = ft_strdup(current_token);
	if (!new_path)
		return (1);
	if (chdir(new_path))
	{
		write(2, "minishell: cd: ", 15);
		write(2, new_path, ft_strlen(new_path));
		write(2, ": No such file or directory\n", 28);
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

int ft_cd_util(char *current_token, char *cwd, char *new_path, t_minishell *minishell)
{
	int	ret;

	ret = 0;
	if (current_token[0] == '/')
		ret = ft_go_path(cwd, new_path, current_token);
	else if (!ft_strcmp(current_token, ".."))
		ret = ft_cd_back_one(cwd, new_path, minishell);
	else if (!ft_strcmp(current_token, "."))
		free(cwd);
	else
	{
		current_token = ft_token_with_spaces(minishell);
		if (chdir(current_token))
		{
			if (errno == EACCES)
				report_perm_denied(minishell, current_token);
			else
				report_no_such_file(minishell, current_token);
			free(cwd);
			return(1);
		}
		free(cwd);
	}
    return (ret);
}

void	ft_cd_back_start(t_minishell *minishell)
{
	t_env	*env;
	char	*home;

	env = minishell->envp;
	home = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "HOME", ft_strlen(env->key) - 1) == 0)
		{
			home = env->value;
			break;
		}
		env = env->next;
	}
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		return;
	}
	if (chdir(home))
		perror("minishell: cd");
}

int	ft_cd(t_minishell *minishell)
{
	char			*new_path;
	char			*cwd;
	int     		result;
	t_token_list	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
			return (report_error(minishell,
					"minishell: cd: getcwd failed", ERR_FILESYSTEM));
	new_path = NULL;
	tmp = minishell->token_list;
	if (!tmp->next)
	{
		ft_cd_back_start(minishell);
		return (0);
	}
	result = ft_cd_util(tmp->next->token->value, cwd, new_path, minishell);
	if (result != 0)
		return (1);
	else
		return (0);
}

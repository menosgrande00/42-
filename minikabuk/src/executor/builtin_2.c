#include "executor.h"

int	ft_cd(char *current_token)
{
	char	*new_path;
	char	*cwd;
    int     result;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("Getcmd Failed");
		return (1);
	}
    new_path = NULL;
	result = ft_cd_util(current_token, cwd, new_path);
    if (result != 0)
        return (1);
	return (0);
}

int	ft_export(t_minishell *minishell)
{
	print_envs_alphabetic(minishell->envp);
	return (0);
}

int ft_unset(t_minishell *minishell, char *current_token)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = minishell->envp;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, current_token) == 0)
		{
			if (prev == NULL)
				minishell->envp = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (0);
}

int ft_exit(t_minishell *minishell)
{
	ft_printf("exit\n");
	free_for_exit(minishell);
	exit(0);
}

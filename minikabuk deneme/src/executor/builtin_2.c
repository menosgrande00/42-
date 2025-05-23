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
	if (!minishell->token_list || 
		!minishell->token_list->next || 
		!minishell->token_list->next->token)
	{
		print_envs_alphabetic(minishell->envp);
		return (0);
	}
	else
		add_env(minishell, minishell->token_list->next->token->value);
	return (0);
}

int	ft_unset(t_minishell *minishell, char *current_token)
{
	t_env	*prev;
	t_env	*it;
	
	if (!current_token)
		return (0);
	if (!is_valid_identifier(current_token))
	{
		ft_printf("minishell: unset: `%s': not a valid identifier\n",
		          current_token);
		return (1);
	}
	prev = NULL;
	it = minishell->envp;
	while (it)
	{
		if (!ft_strcmp(it->key, current_token))
		{
			if (prev)
				prev->next = it->next;
			else
				minishell->envp = it->next;
			free(it->key);
			free(it->value);
			free(it);
			break;
		}
		prev = it;
		it = it->next;
	}
	return (0);
}

int ft_exit(t_minishell *minishell)
{
	ft_printf("exit\n");
	free_for_exit(minishell);
	exit(0);
}

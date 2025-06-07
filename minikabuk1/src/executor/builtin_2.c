#include "executor.h"

int	ft_cd(t_minishell *minishell)
{
	char			*new_path;
	char			*cwd;
    int     		result;
	t_token_list	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf("Getcmd Failed");
		return (1);
	}
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
	return (0);
}

int	ft_export(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	if (!tmp || !tmp->token)
		return (1);
	if (!tmp->next)
	{
		print_envs_alphabetic(minishell->envp);
		return (0);
	}
	while (tmp->next && tmp->next->token->type == TOKEN_WORD)
	{
		add_env(minishell, tmp->next->token->value);
		tmp = tmp->next;
	}
	return (1);
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

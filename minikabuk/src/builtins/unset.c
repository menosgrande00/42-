#include "minishell.h"

int	ft_unset(t_minishell *minishell, char *current_token)
{
	t_env	*prev;
	t_env	*it;
	
	if (!current_token)
		return (0);
	if (!is_valid_identifier(current_token))
	{
		return (report_error(minishell,
					"minishell: unset: not a valid identifier", 
					ERR_INVALID_ARG));
	}
	prev = NULL;
	it = minishell->envp;
	while (it)
	{
		if (!ft_strncmp(it->key, current_token, ft_strlen(it->key) - 1))
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

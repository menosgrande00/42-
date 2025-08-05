#include "minishell.h"

int	ft_export(t_minishell *minishell)
{
	t_token_list	*tmp;

	tmp = minishell->token_list;
	if (!tmp || !tmp->token)
		return (report_error(minishell,
					"minishell: export: invalid arguments", ERR_INVALID_ARG));
	if (!tmp->next)
	{
		print_envs_alphabetic(minishell->envp);
		return (0);
	}
	while (tmp->next && tmp->next->token->type == TOKEN_WORD)
	{
		if (add_env(minishell, tmp->next->token->value))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

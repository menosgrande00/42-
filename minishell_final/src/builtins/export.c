/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:30:06 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/11 19:23:11 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (tmp->next && (tmp->next->token->type == TOKEN_WORD
			|| tmp->next->token->type == TOKEN_COMMAND))
	{
		if (add_env(minishell, tmp->next->token->value) && !tmp->next->next)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

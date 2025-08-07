/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:33:46 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/07 17:33:59 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_minishell *ms, char *current_tok)
{
	t_env	*prev;
	t_env	*it;

	if (!current_tok)
		return (0);
	if (!is_valid_identifier(current_tok))
		return (report_not_valid(ms, current_tok));
	prev = NULL;
	it = ms->envp;
	while (it)
	{
		if (!ft_strncmp(it->key, current_tok, ft_strlen(it->key) - 1))
		{
			if (prev)
				prev->next = it->next;
			else
				ms->envp = it->next;
			ft_free_env_node(it);
			break ;
		}
		prev = it;
		it = it->next;
	}
	return (0);
}

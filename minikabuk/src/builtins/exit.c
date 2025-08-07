/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:24:09 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/07 17:24:10 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error_exit(t_minishell *minishell, char *tmp)
{
	write(2, "minishell: exit: ", 17);
	if (!tmp)
		write(2, minishell->token_list->next->token->value,
			ft_strlen(minishell->token_list->next->token->value));
	else
		write(2, tmp, ft_strlen(tmp));
	write(2, ": numeric argument required\n", 28);
	free_for_exit(minishell);
	exit(255);
}

int	ft_exit(t_minishell *minishell)
{
	int	exit_code;

	exit_code = determine_exit_code(minishell);
	if (exit_code == 255)
		handle_error_exit(minishell, NULL);
	write(1, "exit\n", 5);
	free_for_exit(minishell);
	exit(exit_code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:58:08 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/05 21:46:02 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*create_minishell(void)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
	{
		perror("malloc");
		return (NULL);
	}
	if (calloc_minishell(minishell))
	{
		free(minishell);
		return (NULL);
	}
	minishell->input = NULL;
	minishell->envp = malloc(sizeof(t_env));
	if (!minishell->envp)
	{
		free(minishell->count);
		free(minishell);
		return (NULL);
	}
	minishell->tokens = NULL;
	minishell->exit_status = 0;
	return (minishell);
}

void	run_shell(t_minishell *minishell)
{
	while (1)
	{
		minishell->input = readline("minishell> ");
		if (check_signal() == SIGINT)
			minishell->exit_status = 130;
		if (!minishell->input)
            break ;
		else if (*minishell->input)
		{
			add_history(minishell->input);
			if (tokenizer(minishell))
			{
				parse_tokens(minishell, minishell->token_list);
				execute_command(minishell);
			}
		}
		if (minishell->token_list)
		{
			free_token_list(minishell->token_list);
			minishell->token_list = NULL;
		}
		free(minishell->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell		*minishell;

	(void)argc;
	(void)argv;
	init_signal();
	minishell = create_minishell();
	minishell->envp = init_env(envp);
	minishell->input = "a";
	run_shell(minishell);
	free_for_exit(minishell);
	return (0);
}

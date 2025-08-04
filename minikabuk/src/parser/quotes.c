/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:55:48 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/07/29 20:41:46 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_single_quote_token(t_minishell *minishell, int start,
										int i, t_token **current_token)
{
	char	*tmp;

	tmp = ft_substr(minishell->input, start, i - start);
	if (!tmp)
		return (1);
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
	{
		free(tmp);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	(*current_token)->quotes = 1;
	return (0);
}

static int	sqm(t_minishell *ms, int *i, t_token **current_token, int j)
{
	if (ms->input[j - 1] == ' ' && (ms->input[*i + 1] == ' '
			|| ms->input[*i + 1] == '\0'))
	{
		add_token_to_list(&ms->token_list, *current_token);
		(*i)++;
		return (0);
	}
	if (ms->input[j - 1] != ' ')
	{
		merge_with_previous_token(ms, current_token);
		if ((ms->input[*i + 1] != ' '
				&& ms->input[*i + 1] != '\0'))
		{
			handle_after_quote_text(ms, i, j);
			while (ms->input[*i] != ' ' && ms->input[*i] != '\0')
				(*i)++;
		}
	}
	else if ((ms->input[*i + 1] != ' ' && ms->input[*i + 1] != '\0'))
	{
		remove_quotes_from_input(ms, j, *i);
		*i = j - 2;
	}
	(*i)++;
	return (0);
}

static int	process_single_quote_content(t_minishell *minishell, int *i)
{
	while (minishell->input[*i] && minishell->input[*i] != '\'')
		(*i)++;
	if (minishell->input[*i] != '\'')
	{
		write(2, "syntax error: unclosed quote\n", 29);
		minishell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	single_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	int	start;
	int	j;
	int	ret;

	j = (*i);
	start = ++(*i);
	ret = process_single_quote_content(minishell, i);
	if (ret)
		return (ret);
	ret = create_single_quote_token(minishell, start, *i, current_token);
	if (ret)
		return (1);
	ret = sqm(minishell, i, current_token, j);
	return (ret);
}

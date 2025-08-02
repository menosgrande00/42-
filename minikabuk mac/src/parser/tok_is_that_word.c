/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_is_that_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:29:49 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/07/29 20:29:56 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(const char *input, int *idx)
{
	while (input[*idx] == ' ' || input[*idx] == '\t')
		(*idx)++;
}

static void	advance_word_end(const char *input, int *idx)
{
	while (input[*idx] && input[*idx] != ' ' && input[*idx] != '\t'
		&& input[*idx] != '<' && input[*idx] != '>'
		&& input[*idx] != '|' && input[*idx] != '\''
		&& input[*idx] != '"')
		(*idx)++;
}

static int	create_and_add_token(t_minishell *ms,
	int start, int end, t_token **tok)
{
	char	*tmp;

	*tok = ft_calloc(sizeof(t_token), 1);
	if (*tok == NULL)
		return (0);
	tmp = ft_substr(ms->input, start, end - start);
	if (money_money(ms, &tmp))
		return (1);
	(*tok)->value = ft_strdup(tmp);
	free(tmp);
	add_token_to_list(&ms->token_list, *tok);
	return (1);
}

int	is_that_word(t_minishell *ms, int *i, t_token **tok, int *counter)
{
	int	start;

	while (ms->input[*i] && ms->input[*i] != '|' \
		&& ms->input[*i] != '<' && ms->input[*i] != '>')
	{
		if (*counter == 1)
			skip_spaces(ms->input, i);
		start = *i;
		advance_word_end(ms->input, i);
		if (*i - start == 0)
			break ;
		if (!create_and_add_token(ms, start, *i, tok))
			return (0);
		if (*counter == 1)
		{
			skip_spaces(ms->input, i);
			*counter = 0;
		}
	}
	return (1);
}

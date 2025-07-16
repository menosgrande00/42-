#include "minishell.h"

int double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*tmp;
	int		start;

	start = ++(*i);
	while (minishell->input[*i] && minishell->input[*i] != '"')
	{
		if (minishell->input[*i] == '$' && minishell->input[*i + 1] 
			&& minishell->input[*i + 1] != ' ')
		{
			if (minishell->input[*i] == '$' && minishell->input[*i + 1] == '"')
			{
				(*i)++;
				break;
			}
			tmp = ft_substr(minishell->input, start, (*i) - start);
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
			add_token_to_list(&minishell->token_list, *current_token);
			if (money_money(minishell, i, current_token) && minishell->input[*i] == '"')
				return (1);
			start = *i;
		}
		(*i)++;
	}
	if (minishell->input[*i] != '"')
	{
		printf("syntax error: unclosed quote\n");
		minishell->exit_status = 2;
		return (1);
	}
	tmp = ft_substr(minishell->input, start, (*i) - start);
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
	(*current_token)->quotes = 1;						////////////////////////////////////////
	add_token_to_list(&minishell->token_list, *current_token);
	(*i)++;
	return (0);
}

int	single_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*tmp;
	int		start;

	start = ++(*i);
	while (minishell->input[*i] && minishell->input[*i] != '\'')
		(*i)++;
	if (minishell->input[*i] == '\0')
	{
		printf("syntax error: unclosed quote\n");
		minishell->exit_status = 2;
		return (1);
	}
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
		return (1);
	tmp = ft_substr(minishell->input, start, *i - start);
	if (!tmp)
	{
		free(*current_token);
		return (1);
	}
	(*current_token)->value = tmp;
	(*current_token)->type = TOKEN_WORD;
	add_token_to_list(&minishell->token_list, *current_token);
	(*i)++;
	return (0);
}

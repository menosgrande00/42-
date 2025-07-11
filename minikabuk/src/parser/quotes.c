#include "minishell.h"

int double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*tmp;
	int		start;

    start = ++(*i);
    while (minishell->input[*i] && minishell->input[*i] != '"')
    {
        if (minishell->input[*i] == '$')
        {
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
            if (money_money(minishell, i, current_token))
				return (1);
            start = *i;
        }
        (*i)++;
    }
    if (minishell->input[*i] != '"')
    {
        ft_printf("syntax error: unclosed quote\n");
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
		ft_printf("syntax error: unclosed quote\n");
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

#include "minishell.h"

char *ft_strjoin_free(char *s1, char *s2)
{
    char *res = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return res;
}

char    *double_quotes(t_minishell *minishell, int *i)
{
	char	*tmp;
    char    *buffer;
	int		start;

    start = ++(*i);
    while (minishell->input[*i] && minishell->input[*i] != '"')
    {
        if (minishell->input[*i] == '$')
        {
            tmp = ft_substr(minishell->input, start, (*i) - start);
            buffer = ft_strjoin_free(buffer, tmp);
            (*i)++;
            tmp = money_money(minishell, i);
            if (tmp[0] == "")
                return (tmp);
            buffer = ft_strjoin_free(buffer, tmp);
            start = *i;
        }
        else
            (*i)++;
    }
    if (minishell->input[*i] != '"')
    {
        printf("syntax error: unclosed quote\n");
        free(buffer);
        return (NULL);
    }
    tmp = ft_substr(minishell->input, start, (*i) - start);
    buffer = ft_strjoin_free(buffer, tmp);
    (*i)++;
    return (buffer);
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

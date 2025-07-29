#include "minishell.h"

int	handle_quote_merging(t_minishell *minishell, int *i, t_token **tok, int j)
{
	if (j > 0 && minishell->input[j - 1] == '|' && minishell->input[*i + 1] != '"')
	{
		add_token_to_list(&minishell->token_list, *tok);
		remove_quotes_from_input(minishell, j, *i);
		*i = j + ft_strlen((*tok)->value);
		return (0);
	}	
	if (minishell->input[j - 1] == ' ' && (minishell->input[*i + 1] == ' ' 
		|| minishell->input[*i + 1] == '\0'))
	{
		add_token_to_list(&minishell->token_list, *tok);
		(*i)++;
		return (0);
	}
	if (minishell->input[j - 1] != ' ')
	{
		merge_with_previous_token(minishell, tok);
		if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
		{
			handle_after_quote_text(minishell, i, j);
			while (minishell->input[*i] != ' ' && minishell->input[*i] != '\0')
				(*i)++;
		}
	}
	else if ((minishell->input[*i + 1] != ' ' && minishell->input[*i + 1] != '\0'))
	{
		remove_quotes_from_input(minishell, j, *i);
		*i = j - 2;
	}
	(*i)++;
	return (0);
}

static int	create_quote_token(t_minishell *minishell, int start, int i, t_token **current_token)
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

int	process_quote_content(t_minishell *minishell, int *i, int *start)
{
	int	ret;

	while (minishell->input[*i] && minishell->input[*i] != '"')
	{
		if (minishell->input[*i] == '$' && minishell->input[*i + 1] 
			&& minishell->input[*i + 1] != ' ')
		{
			ret = handle_dollar_in_quotes(minishell, i, start);
			if (ret != 0)
			{
				if (ret == -1)
				    return 1;
				else
				    return 0;
			}
		}
		(*i)++;
	}
	if (minishell->input[*i] != '"')
	{
		write(2, "syntax error: unclosed quote\n", 29);
		minishell->exit_status = 2;
		return (1);
	}
	return (0);
}

int	double_quotes(t_minishell *minishell, int *i, t_token **current_token)
{
	int	start;
	int	j;
	int	ret;

	j = (*i);
	start = ++(*i);
	ret = process_quote_content(minishell, i, &start);
	if (ret)
		return (ret);
	ret = create_quote_token(minishell, start, *i, current_token);
	if (ret)
		return (1);
	ret = handle_quote_merging(minishell, i, current_token, j);
	return (ret);
}

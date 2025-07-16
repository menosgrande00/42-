#include "parser.h"

int	is_that_word(t_minishell *minishell, int *i, t_token **current_token, int *counter)
{
	char	*tmp;
	int		start;

	while(minishell->input[*i] && minishell->input[*i] != '|'
			&& minishell->input[*i] != '<' && minishell->input[*i] != '>')
	{
		if(*counter == 1)
			while(minishell->input[*i] == ' ' || minishell->input[*i] == '\t')
				(*i)++;
		if (minishell->input[*i] == '$')
		{
			if (money_money(minishell, i, current_token))
				return (1);
			add_token_to_list(&minishell->token_list, *current_token);
		}
		start = *i;
		if(*counter == 1)
		{
			while(minishell->input[*i] && minishell->input[*i] != ' ' 
					&& minishell->input[*i] != '\t' && minishell->input[*i] != '<'
					&& minishell->input[*i] != '>' && minishell->input[*i] != '|'
					&& minishell->input[*i] != '\'' && minishell->input[*i] != '\"'
					&& minishell->input[*i] != '$')
			(*i)++;
		}
		else
		{
			while(minishell->input[*i] && minishell->input[*i] != '\t' && minishell->input[*i] != '<'
					&& minishell->input[*i] != '>' && minishell->input[*i] != '|'
					&& minishell->input[*i] != '\'' && minishell->input[*i] != '\"'
					&& minishell->input[*i] != '$')
		    (*i)++;
		}
		if (*i - start == 0)
			break;
		*current_token = ft_calloc(sizeof(t_token), 1);
		if (!*current_token)
		    return (0);
		tmp = ft_substr(minishell->input, start, *i - start);
		(*current_token)->value = tmp;
		add_token_to_list(&minishell->token_list, *current_token);
		if (*counter == 1)
		{
			while(minishell->input[*i] == ' ' || minishell->input[*i] == '\t')
				(*i)++;
			*counter = 0;
		}
	}
    return (1);
}

int	is_operator(char *str, t_token **current_token)
{
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
		return (0);
	if ((str[0] == '>' && str[1] == '>') || (str[0] == '<' && str[1] == '<')
		|| (str[0] == '|' && str[1] == '|'))
	{
		(*current_token)->value = ft_substr(str, 0, 2);
		if (!(*current_token)->value)
		{
			free(*current_token);
			return (0);
		}
		return (2);
	}
	else if (str[0] == '|' || str[0] == '<' || str[0] == '>')
	{
		(*current_token)->value = ft_substr(str, 0, 1);
		if (!(*current_token)->value)
		{
			free(*current_token);
			return (0);
		}
		return (1);
	}
	free(*current_token);
	return (0);
}

int	split_input(t_minishell *minishell)
{
	t_token	*current_token;
	int	i;
	int	ret;
	int	counter;

	counter = 1;
	i = 0;
	while (minishell->input[i])
	{
		while (minishell->input[i] == ' ' || minishell->input[i] == '\t')
			i++;
		if ((minishell->input[i]) == '\"')
		{
            ret = double_quotes(minishell, &i, &current_token);
            if (ret != 0)
                return (ret);
        }
		if ((minishell->input[i]) == '\'')
		{
            ret = single_quotes(minishell, &i, &current_token);
            if (ret != 0)
                return (ret);
        }
		ret = is_operator(&minishell->input[i], &current_token);
		if (ret)
		{
			counter = 1;
			add_token_to_list(&minishell->token_list, current_token);
			i += ret;
		}
		else
			is_that_word(minishell, &i, &current_token, &counter);
	}
	return (0);
}

t_token_list	*tokenizer(t_minishell *minishell)
{
	minishell->token_list = NULL;

	if (!minishell || !(minishell)->input)
        return (NULL);
	split_input(minishell);
	return (minishell->token_list);
}

#include "minishell.h"

int	is_that_word(t_minishell *minishell, int *i, t_token **current_token)
{
	int start;

	start = *i;

	while (minishell->input[*i] && minishell->input[*i] != '\t' 
			&& minishell->input[*i] != ' ' && minishell->input[*i] != '|'
			&& minishell->input[*i] != '<' && minishell->input[*i] != '>')
		(*i)++;
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
		return (0);
	(*current_token)->value = ft_substr(minishell->input, start, *i - start);
	if (!(*current_token)->value)
	{
		free(*current_token);
		return (0);
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

void	split_input(t_minishell *minishell)
{
	t_token	*current_token;
	int	i;
	int	ret;

	i = 0;
	while (minishell->input[i])
	{
		while (minishell->input[i] == ' ' || minishell->input[i] == '\t')
			i++;
		ret = is_operator(&minishell->input[i], &current_token);
		if (ret)
		{
			add_token_to_list(&minishell->token_list, current_token);
			i += ret;
		}
		else 
		{
			if (!is_that_word(minishell, &i, &current_token))
				return;
			add_token_to_list(&minishell->token_list, current_token);
		}
	}
}

t_token_list	*tokenizer(t_minishell *minishell)
{
	minishell->token_list = NULL;

	if (!minishell || !(minishell)->input)
        return (NULL);
	split_input(minishell);
	return (minishell->token_list);
}

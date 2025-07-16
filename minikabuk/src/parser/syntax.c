#include "minishell.h"
static char *get_env_value(t_env *envp, char *key)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

static	int	env_expand(t_minishell *minishell, int *i, t_token **current_token)
{
	char	*key;
	char	*value;
	int		start;
	int		len;

	start = *i;
	while (minishell->input[*i] && (ft_isalnum(minishell->input[*i]) || 
		minishell->input[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 0)
		return (0);
	key = ft_substr(minishell->input, start, len);
	if (!key)
		return (1);
	value = get_env_value(minishell->envp, key);
	free(key);
	*current_token = ft_calloc(sizeof(t_token), 1);
	if (!*current_token)
		return (1);
	if (value)
		(*current_token)->value = ft_strdup(value);
	else
		(*current_token)->value = ft_strdup("");
	if (!(*current_token)->value)
	{
		free(*current_token);
		return (1);
	}
	(*current_token)->type = TOKEN_WORD;
	add_token_to_list(&minishell->token_list, *current_token);
	return (0);
}

static	int	money_with_que(t_minishell *minishell, int *i, t_token **current_token)
{
	char    *tmp;

	tmp = ft_itoa(minishell->exit_status);
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

int	money_money(t_minishell *minishell, int *i, t_token **current_token)
{
	(*i)++;
	if (minishell->input[*i] == '?')
	{
		if(!money_with_que(minishell, i, current_token))
			return (1);
	}
	else if (minishell->input[*i] == '\0' || minishell->input[*i] == ' ')
		printf("$\n");
	else
		if(!env_expand(minishell, i, current_token))
			return (1);
	return (0);
}

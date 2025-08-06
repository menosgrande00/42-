#include "minishell.h"

void	free_double(char **str)
{
	int	i;

	if(!str)
		return ;
	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env_list(t_env *list)
{
	t_env	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_token_list(t_token_list *list)
{
	t_token_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->token)
		{
			if (tmp->token->value)
				free(tmp->token->value);
			free(tmp->token);
		}
		free(tmp);
	}
}

int	free_for_exit(t_minishell *minishell)
{
	if (minishell->token_list)
		free_token_list(minishell->token_list);
	if (minishell->envp)
		free_env_list(minishell->envp);
	if (minishell->count)
		free(minishell->count);
	free(minishell->input);
	free_double(minishell->export);
	free_double(minishell->tokens);
	free(minishell);
	return(0);
}

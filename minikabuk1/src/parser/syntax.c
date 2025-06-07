#include "minishell.h"
static	int	env_expand(t_minishell *minishell, int *i, t_token **current_token)
{
	t_env	**arg;
	int		x;
	char	*env;

	x = *i;
	while(minishell->input[x] && minishell->input[x] != ' ')
		x++;
	env = malloc(x + 1);
	arg = env_to_array(minishell->envp);
	
}
static	int	do_op(t_minishell *minishell, int *i, t_token **current_token)
{

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
	char    *tmp;

	(*i)++;
	if (minishell->input[*i] == '?')
	{
		if(!money_with_que(minishell, i, current_token))
			return (1);
	}
	else if (minishell->input[*i] == '(' && minishell->input[*i + 1] == '(')
	{
		if (ft_strcmp(minishell->input + *i, "))") || 
			!do_op(minishell, i, current_token))
			return (1);
	}
	else
		if(!env_expand(minishell, i, current_token))
			return (1);
	return (0);
}

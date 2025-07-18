#include "minishell.h"
static char *get_env_value(t_env *envp, char *key)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
		{
			tmp = ft_strdup(envp->value);
			return (tmp);
		}
		envp = envp->next;
	}
	return (tmp);
}

// static	int	do_op(t_minishell *minishell, int *i, t_token **current_token)
// {
// 	return (0);
// }

char	*money_money(t_minishell *minishell, int *i)
{
	char 	*key;
    char 	*val;
    int   	start;

	start = *i;
	if (minishell->input[*i] == '?')
	{
		(*i)++;
		val = ft_itoa(minishell->exit_status);
	}
	// else if (minishell->input[*i] == '(' && minishell->input[*i + 1] == '(')
	// {
	// 	if (ft_strcmp(minishell->input + *i, "))") || 
	// 		!do_op(minishell, i, current_token))
	// 		return (1);
	// }
	else
		while (minishell->input[*i] && (ft_isalnum(minishell->input[*i]) || 
				minishell->input[*i]=='_'))
        	(*i)++;
		key = ft_substr(minishell->input, start, *i - start);
    	val = get_env_value(minishell->envp, key);
		free(key);
	return (val);
}

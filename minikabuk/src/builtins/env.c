#include "minishell.h"

int ft_env(t_minishell *minishell)
{
	t_env *tmp;

	tmp = minishell->envp;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '='))
		{
			printf("%s", tmp->key);
			printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}

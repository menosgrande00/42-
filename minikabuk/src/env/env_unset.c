#include "minishell.h"

void	unset_one(t_env **env, const char *key)
{
    t_env   *curr;
    t_env   *prev;

    if (!is_valid_key((char *)key))
	{
		ft_printf("unset: `%s': not a valid identifier\n", key);
		return ;
	}
    curr = *env;
    prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

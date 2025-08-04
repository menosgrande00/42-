#include "environment.h"

t_env	*env_node(char *str)
{
	t_env	*node;
	char	*eq;
	int		i;

	eq = ft_strchr(str, '=');
	if (!eq)
	{
		return (NULL);
	}
	i = ft_strlen(str) - ft_strlen(eq);
	node = malloc(sizeof(t_env));
	if (!node || !str)
		return (NULL);
	node->key = ft_substr(str, 0, i);
	if(!(node->key))
	{
		free(node);
		return (NULL);
	}
	if (eq)
		node->value = ft_strdup(eq + 1);
	else
		node->value = ft_strdup("");
	if (!(node->value))
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

t_env	*init_env(char **envp)
{
	t_env	*first;
	t_env	*last;
	t_env	*node;
	int		i;

	first = NULL;
	last = NULL;
	node = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while(envp[i])
	{
		node = env_node(envp[i]);
		if (!node)
		{
		    i++;
		    continue;
		}
		if (first == NULL)
		{
			first = node;
			last = node;
		}
		else
		{
			last->next = node;
			last = node;
		}
		i++;
	}
	return (first);
}

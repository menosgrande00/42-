#include "environment.h"

static int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while(env)
	{
		env = env->next;
		size++;
	}
	return (size);
}

static t_env	**env_to_array(t_env *env)
{
	int     i;
	int     size;
	t_env	**arr;

	i = 0;
	size = env_size(env);
	arr = malloc(sizeof(t_env *) * (size + 1));
	if (!arr)
		return (NULL);
	while (env)
	{
		if (!arr)
			return (NULL);
		arr[i++] = env;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

static void	sort_env_array(t_env **arr)
{
	int		i;
	int		j;
	int		size;
	t_env	*temp;

	i = 0;
	size = 0;
	while (arr[size])
		size++;
	while(i < size - 1)
	{
		j = 0;
		while (j < size - 1)
		{
			if (ft_strncmp(arr[j]->key, arr[j + 1]->key, 1000) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_envs_alphabetic(t_env *env)
{
	t_env   **arr;
	int     i;

	i = 0;
	arr = env_to_array(env);
	if (!arr)
		return;
	sort_env_array(arr);
	while (arr[i])
	{
		ft_printf("%s", arr[i]->key);
		if (arr[i]->value)
			ft_printf("=%s", arr[i]->value);
		ft_printf("\n");
		i++;
	}
	free(arr);
}

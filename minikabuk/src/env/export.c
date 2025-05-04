#include "minishell.h"

int	is_valid_key(char *key)
{
	int i;

	i = 0;
	if (!key || !(ft_isalpha(key[0] || key[0] == '_')))
		return (0);
	while (key[i])
	{
		if (!(ft_isalnum(key[i] || key[i] == '_')))
			return (0);
		i++;
	}
	return (1);
}

static int parse_export_arg(const char *arg, char **key, char **value)
{
    char *eq = ft_strchr(arg, '=');
    *value = NULL;
    if (eq)
    {
        *key = ft_substr(arg, 0, eq - arg);
        *value = ft_strdup(eq + 1);
    }
    else
        *key = ft_strdup(arg);
    if (!is_valid_key(*key))
    {
        ft_printf("export: `%s': not a valid identifier\n", *key);
        free(*key);
        if (*value) free(*value);
        return (0);
    }
    return (1);
}

static int update_existing_env(t_env *env, const char *key, char *value)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            if (value)
            {
                free(env->value);
                env->value = value;
            }
            return (1);
        }
        env = env->next;
    }
    return (0);
}

void export_one(t_env **env_list, const char *arg)
{
    char *key;
    char *value;
    t_env *new;

    if (!parse_export_arg(arg, &key, &value))
        return;
    if (update_existing_env(*env_list, key, value))
    {
        free(key);
        return;
    }
    new = malloc(sizeof(t_env));
    new->key = key;
    new->value = value;
    new->next = *env_list;
    *env_list = new;
}

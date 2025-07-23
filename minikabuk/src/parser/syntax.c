#include "minishell.h"

char *get_env_value(t_env *envp, char *key)
{
	while (envp)
	{
		if (ft_strcmp(envp->key, key) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

char	*extract_env_key(char *tmp, int *j)
{
	char	*key;
	int		start;
	int		len;
	int		i;

	i = *j;
	start = *j;
	while (tmp[i] && (ft_isalnum(tmp[i]) || 
		tmp[i] == '_'))
		(i)++;
	len = i - start;
	if (len == 0)
		return (NULL);
	key = ft_substr(tmp, start, len);
	return (key);
}

char	*replace_tmp_envp(char *tmp, int *j, char *value, int len)
{
	int 	i;
	int		y;
	int		k;
	char	*tmp2;

	i = 0;
	y = (*j) + len + 1;
	tmp2 = malloc(ft_strlen(tmp) + ft_strlen(value) + 1 - len);
	while (tmp[i] != '$')
	{
		tmp2[i] = tmp[i];
		i++;
	}
	while (tmp[y])
	{
		tmp2[i] = tmp[y];
		i++;
		y++;
	}
	k = 0;
	while (value[k])
	{
		tmp2[i] = value[k];
		i++;
		k++;
	}
	tmp2[i] = '\0';
	return(tmp2);
}

char	*env_expand(t_minishell *minishell, char *tmp, int *j)
{
	char	*key;
	char	*value;

	(*j)++;
	key = extract_env_key(tmp, j);
	if (!key)
		return (NULL);
	value = get_env_value(minishell->envp, key);
	if (!value)
		return (NULL);
	(*j)--;
	tmp = replace_tmp_envp(tmp, j, value, ft_strlen(key));
	free(key);
	return (tmp);
}

char	*replace_tmp(char *tmp, int *j, char *status)
{
	int 	i;
	int		y;
	char	*last;

	i = 0;
	last = ft_strdup(tmp + ((*j) + 2));
	while (status[i])
	{
		tmp[*j] = status[i];
		(*j)++;
		i++;
	}
	y = (*j);
	i = 0;
	while (last[i])
	{
		tmp[y] = last[i];
		y++;
		i++;
	}
	tmp[y] = '\0';
	return(tmp);
}

int	money_money_process(t_minishell *minishell, char *tmp, int *j)
{
	char	*status;

	status = ft_itoa(minishell->exit_status);
	if (!status)
		return (1);
	replace_tmp(tmp, j, status);
	return (0);		
}

int	money_money(t_minishell *minishell, char **tmp)
{
	int	j;
	char *new_tmp;

	j = 0;
	while ((*tmp)[j])
	{
		if ((*tmp)[j] == '$')
		{
			if ((*tmp)[(j) + 1] && (*tmp)[(j) + 1] == '?')
			{
				if(money_money_process(minishell, *tmp, &j))
					return(1);
			}
			else if ((*tmp)[(j) + 1])
			{
				new_tmp = env_expand(minishell, *tmp, &j);
				if (!new_tmp)
					return (1);
				free(*tmp);
				*tmp = new_tmp;
			}
		}
		j++;
	}
	return (0);
}

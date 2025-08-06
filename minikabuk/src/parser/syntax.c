/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:35:24 by omerfarukon       #+#    #+#             */
/*   Updated: 2025/08/06 20:31:46 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_tmp_envp(char *tmp, int *j, char *value, int len)
{
	int		i;
	int		y;
	int		k;
	char	*tmp2;

	i = 0;
	y = (*j) + len + 1;
	tmp2 = malloc(ft_strlen(tmp) + ft_strlen(value) + 1 - len);
	if (!tmp2)
		return (NULL);
	while (tmp[i] != '$')
	{
		tmp2[i] = tmp[i];
		i++;
	}
	while (tmp[y])
		tmp2[i++] = tmp[y++];
	k = 0;
	while (value[k])
		tmp2[i++] = value[k++];
	tmp2[i] = '\0';
	return (tmp2);
}

char	*env_expand(t_minishell *minishell, char *tmp, int *j)
{
	char	*key;
	char	*value;
	char	*new_tmp;

	(*j)++;
	key = extract_env_key(tmp, j);
	if (!key)
		return (NULL);
	value = get_env_value(minishell->envp, key);
	if (!value)
	{
		free(key);
		return (NULL);
	}
	(*j)--;
	new_tmp = replace_tmp_envp(tmp, j, value, ft_strlen(key));
	free(key);
	return (new_tmp);
}

int	money_money_process(t_minishell *minishell, char *tmp, int *j)
{
	char	*status;
	char	*new_tmp;

	status = ft_itoa(minishell->exit_status);
	if (!status)
		return (1);
	new_tmp = replace_tmp(tmp, j, status);
	free(status);
	if (!new_tmp)
		return (1);
	return (0);
}

static int	money_expand(t_minishell *minishell, char **tmp)
{
	int		j;
	char	*new_tmp;

	j = -1;
	while ((*tmp)[++j])
	{
		if ((*tmp)[j] == '$')
		{
			if ((*tmp)[j + 1] == '?')
			{
				if (money_money_process(minishell, *tmp, &j))
					return (1);
			}
			else if ((*tmp)[j + 1])
			{
				new_tmp = env_expand(minishell, *tmp, &j);
				if (!new_tmp)
					return (1);
				free(*tmp);
				*tmp = new_tmp;
			}
		}
	}
	return (0);
}

int	money_money(t_minishell *minishell, char **tmp)
{
	int		j;

	if (money_expand(minishell, tmp))
		return (1);
	j = -1;
	while ((*tmp)[++j])
		if ((*tmp)[j] == 1)
			(*tmp)[j] = '$';
	return (0);
}

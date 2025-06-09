/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 05:41:43 by agurses           #+#    #+#             */
/*   Updated: 2025/04/08 11:54:55 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strcspn(const char *s, const char *charset)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (charset[j])
		{
			if (s[i] == charset[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_strlen_for_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] || str[i] == '\n')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*new_str;
	int		i;

	len = ft_strlen(s);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

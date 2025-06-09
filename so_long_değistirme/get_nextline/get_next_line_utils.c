/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:31:26 by agurses           #+#    #+#             */
/*   Updated: 2024/12/27 16:36:15 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*temp;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = ft_strlen(str1) + ft_strlen(str2);
	temp = (char *)malloc(sizeof(char) * (size + 1));
	if (!temp || !str1 || !str2)
		return (NULL);
	while (str1[i] != '\0')
	{
		temp[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
		temp[i++] = str2[j++];
	temp[size] = '\0';
	return (temp);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, char c)
{
	char	a;

	a = c;
	while (a != *s)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*res;

	res = malloc(size * count);
	if (!res)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}

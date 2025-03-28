/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 05:52:30 by agurses           #+#    #+#             */
/*   Updated: 2025/03/28 06:03:18 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_unicode_checker(char *message)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *)message;
	i = 0;
	while (str[i])
	{
		if (str[i] > 127)
		{
			ft_strcpy(message, UNICODE_MARKER);
			return (message);
		}
		i++;
	}
	return (message);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

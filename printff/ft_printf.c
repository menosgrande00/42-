/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:05:50 by oonal             #+#    #+#             */
/*   Updated: 2024/12/03 19:51:48 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(const char *str, va_list va, unsigned int *counter)
{
	int	c;

	if (*str == 'c')
	{
		c = va_arg(va, int);
		*counter += write(1, &c, 1);
	}
	else if (*str == 'u')
		ft_putunbr(va_arg(va, unsigned int), counter);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr(va_arg(va, int), counter);
	else if (*str == 's')
		ft_putstr(va_arg(va, const char *), counter);
	else if (*str == 'x' || *str == 'X')
		ft_puthex(va_arg(va, unsigned int), *str, counter);
	else if (*str == 'p')
	{
		ft_putstr("0x", counter);
		ft_puthexp(va_arg(va, unsigned long), counter);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			va;
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	va_start(va, str);
	while (str)
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
			{
				count += write(1, "%", 1);
			}
			else
				ft_flags(&str[i + 1], va, &count);
		}
		else
			count += write(1, &str[i], 1);
	}
	return (count);
}

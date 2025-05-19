/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:51:06 by agurses           #+#    #+#             */
/*   Updated: 2024/12/05 18:09:20 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(const char *str, va_list args, unsigned int *counter)
{
	int	result;

	if (*str == 'c')
	{
		result = va_arg(args, int);
		*counter += write(1, &result, 1);
	}
	else if (*str == 'u')
		ft_putunbr(va_arg(args, unsigned int), counter);
	else if (*str == 'd' || *str == 'i')
		ft_putnbr(va_arg(args, int), counter);
	else if (*str == 's')
		ft_putstr(va_arg(args, const char *), counter);
	else if (*str == 'x' || *str == 'X')
		ft_puthex(va_arg(args, unsigned int), *str, counter);
	else if (*str == 'p')
		ft_puthexp(va_arg(args, unsigned long), counter);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	counter;

	if (!str)
		return (-1);
	i = 0;
	counter = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				counter += write(1, "%", 1);
			else
				ft_flags(&str[i + 1], args, &counter);
			i++;
		}
		else
			counter += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (counter);
}

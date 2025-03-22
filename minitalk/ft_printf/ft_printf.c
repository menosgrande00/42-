/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:37:28 by omerfarukon       #+#    #+#             */
/*   Updated: 2024/12/04 00:21:19 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flags(const char *str_char, va_list va, unsigned int *counter)
{
	int	result_c;

	if (*str_char == 'c')
	{
		result_c = va_arg(va, int);
		*counter += write(1, &result_c, 1);
	}
	else if (*str_char == 'u')
		ft_putunbr(va_arg(va, unsigned int), counter);
	else if (*str_char == 'd' || *str_char == 'i')
		ft_putnbr(va_arg(va, int), counter);
	else if (*str_char == 's')
		ft_putstr(va_arg(va, const char *), counter);
	else if (*str_char == 'x' || *str_char == 'X')
		ft_puthex(va_arg(va, unsigned long), *str_char, counter);
	else if (*str_char == 'p')
		ft_puthexp(va_arg(va, unsigned long), counter);
	else
	{
		*counter += write(1, "%", 1);
		*counter += write(1, &str_char[0], 1);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	result;

	if (!str)
		return (-1);
	i = 0;
	result = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				result += write(1, "%", 1);
			else
				ft_flags(&str[i + 1], args, &result);
			i++;
		}
		else
			result += write(1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (result);
}

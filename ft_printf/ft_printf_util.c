/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:54:26 by oonal             #+#    #+#             */
/*   Updated: 2024/12/04 19:07:08 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(const char *s, unsigned int *counter)
{
	int	i;

	i = 0;
	if (!s)
	{
		*counter += write(1, "(null)", 6);
		return ;
	}
	while (s[i] != '\0')
	{
		*counter += write(1, &s[i], 1);
		i++;
	}
	return ;
}

void	ft_putnbr(int n, unsigned int *counter)
{
	char	res;

	if (n == -2147483648)
	{
		ft_putnbr(n / 10, counter);
		*counter += write(1, "8", 1);
	}
	else if (n < 0)
	{
		*counter += write(1, "-", 1);
		ft_putnbr(-n, counter);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, counter);
		res = (n % 10) + '0';
		*counter += write(1, &res, 1);
	}
}

void	ft_putunbr(unsigned int n, unsigned int *counter)
{
	char	res;

	if (n > 9)
		ft_putunbr(n / 10, counter);
	res = (n % 10) + '0';
	*counter += write(1, &res, 1);
}

void	ft_puthex(unsigned long hex, char uppercase, unsigned int *counter)
{
	char	*alpha;

	if (uppercase == 'X')
		alpha = "ABCDEF";
	else if (uppercase == 'x')
		alpha = "abcdef";
	if ((hex / 16) == 0)
	{
		if ((hex % 16) < 10)
			ft_putnbr(hex % 16, counter);
		else
			*counter += write(1, &alpha[hex % 16 - 10], 1);
		return ;
	}
	ft_puthex(hex / 16, uppercase, counter);
	if (hex % 16 < 10)
		ft_putnbr(hex % 16, counter);
	else
		*counter += write(1, &alpha[hex % 16 - 10], 1);
}

void	ft_puthexp(unsigned long hex, unsigned int *counter)
{
	if (hex == 0)
	{
		*counter += write(1, "(nil)", 5);
		return ;
	}
	else
	{
		*counter += write(1, "0x", 2);
		ft_puthex(hex, 'x', counter);
	}
}

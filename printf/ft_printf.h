/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:37:35 by omerfarukon       #+#    #+#             */
/*   Updated: 2024/12/03 23:37:36 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

void	ft_putstr(const char *s, unsigned int *counter);
void	ft_putnbr(int n, unsigned int *counter);
void	ft_putunbr(unsigned int n, unsigned int *counter);
void	ft_puthex(unsigned int hex, char uppercase, unsigned int *counter);
void	ft_puthexp(unsigned long hex, unsigned int *counter);
int		ft_printf(const char *str, ...);

#endif
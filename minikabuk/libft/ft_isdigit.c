/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agurses <agurses@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:26:11 by agurses           #+#    #+#             */
/*   Updated: 2024/11/15 17:07:54 by agurses          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int x)
{
	if ((x > 47 && x < 58))
		return (1);
	return (0);
}

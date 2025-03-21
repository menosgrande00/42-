/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:24 by oonal             #+#    #+#             */
/*   Updated: 2025/03/17 18:32:53 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max_value(t_stack *stack)
{
	int		min;
	t_stack	*tmp;

	min = INT_MIN;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value > min)
			min = tmp->value;
		tmp = tmp->next;
	}
	return (min);
}

int	find_min_value(t_stack *stack)
{
	int		max;
	t_stack	*tmp;

	max = INT_MAX;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value < max)
			max = tmp->value;
		tmp = tmp->next;
	}
	return (max);
}

int	find_max_index(t_stack *stack)
{
	int		min;
	int		max_index;
	int		i;
	t_stack	*tmp;

	min = INT_MIN;
	max_index = -1;
	i = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value > min)
		{
			min = tmp->value;
			max_index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (max_index);
}

int	find_min_index(t_stack *stack)
{
	int		max;
	int		min_index;
	int		i;
	t_stack	*tmp;

	max = INT_MAX;
	min_index = -1;
	i = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value < max)
		{
			max = tmp->value;
			min_index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (min_index);
}

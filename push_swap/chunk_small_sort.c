/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_small_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:33 by oonal             #+#    #+#             */
/*   Updated: 2025/03/18 19:15:45 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_three(t_stack **a)
{
	int	second;
	int	third;

	if (stack_size(*a) == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);
		return ;
	}
	second = (*a)->next->value;
	third = (*a)->next->next->value;
	if ((*a)->value > second && (*a)->value > third)
	{
		ra(a);
		if (second > third)
			sa(a);
	}
	else if (second > (*a)->value && second > third)
	{
		rra(a);
		if (second > third)
			sa(a);
	}
	else if ((*a)->value > second)
		sa(a);
}

void	sort_five_part1(t_stack **a, t_stack **b, int size)
{
	int	min_index;

	min_index = find_min_index(*a);
	while (min_index > 0)
	{
		ra(a);
		min_index--;
	}
	pb(a, b);
	if (size == 5)
	{
		min_index = find_min_index(*a);
		while (min_index > 0)
		{
			ra (a);
			min_index--;
		}
		pb (a, b);
	}
}

void	sort_five(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size <= 3)
	{
		sort_three (a);
		return ;
	}
	sort_five_part1 (a, b, size);
	sort_three (a);
	pa (a, b);
	if (size == 5)
		pa (a, b);
}

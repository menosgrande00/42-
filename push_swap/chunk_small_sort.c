/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_small_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:33 by oonal             #+#    #+#             */
/*   Updated: 2025/03/19 18:06:00 by oonal            ###   ########.fr       */
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

static void	bring_min_to_top(t_stack **a, int pos)
{
	int	size;

	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			rra(a);
	}
}

void	sort_five(t_stack **a, t_stack **b)
{
	int	min1_pos;
	int	min2_pos;

	min1_pos = find_min_index(*a);
	bring_min_to_top(a, min1_pos);
	pb(a, b);
	min2_pos = find_min_index(*a);
	bring_min_to_top(a, min2_pos);
	pb(a, b);
	sort_three(a);
	if ((*b)->value < (*b)->next->value)
		sb(b);
	pa(a, b);
	pa(a, b);
}

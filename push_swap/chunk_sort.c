/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omerfarukonal <omerfarukonal@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:30 by oonal             #+#    #+#             */
/*   Updated: 2025/03/21 15:49:53 by omerfarukon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	send_chunk_to_b(t_stack **a, t_stack **b, int lower, int upper)
{
	int	init_size;
	int	i;

	init_size = stack_size(*a);
	i = 0;
	while (i < init_size)
	{
		if ((*a)->value >= lower && (*a)->value < upper)
			pb(a, b);
		else
			ra(a);
		i++;
	}
}

void	send_max_to_a(t_stack **a, t_stack **b)
{
	int	max_idx;
	int	size_b;
	int	i;

	max_idx = find_max_index(*b);
	size_b = stack_size(*b);
	i = -1;
	if (max_idx <= size_b / 2)
	{
		while (++i < max_idx)
			rb(b);
	}
	else
	{
		while (++i < size_b - max_idx)
			rrb(b);
	}
	pa(a, b);
}

void	chunk_sort_part1(t_stack **a, t_stack **b)
{
	int	range;
	int	chunk_count;
	int	i;
	int	lower;
	int	upper;

	i = -1;
	chunk_count = 5;
	range = find_max_value(*a) - find_min_value(*a);
	if (stack_size(*a) > 100)
		chunk_count = 6 + stack_size(*a) / 100;
	while (++i < chunk_count)
	{
		lower = find_min_value(*a) + (range * i / chunk_count);
		upper = find_min_value(*a) + (range * (i + 1) / chunk_count);
		send_chunk_to_b(a, b, lower, upper);
	}
	while (*a)
		pb(a, b);
	while (*b)
		send_max_to_a(a, b);
}

void	chunk_sort(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size <= 1 || is_sorted(*a))
		return ;
	if (size <= 3)
	{
		sort_three(a);
		return ;
	}
	if (size <= 5)
	{
		sort_five(a, b);
		return ;
	}
	chunk_sort_part1(a, b);
}

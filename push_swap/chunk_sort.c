#include "push_swap.h"
void send_chunk_to_b(t_stack **a, t_stack **b, int lower, int upper)
{
	int init_size;
	int i;

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

void send_max_to_a(t_stack **a, t_stack **b)
{
	int max_idx = find_max_index(*b);
	int size_b = stack_size(*b);
	int i = -1;
	
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

void chunk_sort_part1(t_stack **a, t_stack **b)
{
	int size;
	int min;
	int max;
	int range;
	int chunk_count;
	int i;
	
	i = -1;
	chunk_count = 5;
	size = stack_size(*a);
	min = find_min_value(*a);
	max = find_max_value(*a);
	range = max - min;
	if (size >= 500)
		chunk_count = 11;
	while (++i < chunk_count) 
	{
		int lower = min + (range * i / chunk_count);
		int upper = min + (range * (i + 1) / chunk_count);
		send_chunk_to_b(a, b, lower, upper);
	}
	while (*a)
		pb(a, b);
	while (*b)
		send_max_to_a(a, b);
}

void chunk_sort(t_stack **a, t_stack **b)
{
	int size;

	size = stack_size(*a);
	if (size <= 1 || is_sorted(*a))
		return;
	if (size <= 3) 
	{
		sort_three(a);
		return;
	}
	if (size <= 5) 
	{
		sort_five(a, b);
		return;
	}
	chunk_sort_part1(a, b);
}

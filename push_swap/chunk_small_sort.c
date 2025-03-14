#include "push_swap.h"

void sort_three(t_stack **a) 
{
	if (!*a || stack_size(*a) < 2 || is_sorted(*a)) 
		return;
	if (stack_size(*a) == 2) 
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);
		return;
	}

	int first = (*a)->value;
	int second = (*a)->next->value;
	int third = (*a)->next->next->value;

	if (first > second && first > third) 
	{
		ra(a);
		if (second > third)
			sa(a);
	} 
	else if (second > first && second > third) 
	{
		rra(a);
		if (first > third)
			sa(a);
	} 
	else if (first > second)
		sa(a);
}
void sort_five_part1(t_stack **a, t_stack **b, int size)
{
	int min_index;
	
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
			ra(a);
			min_index--;
		}
		pb(a, b);
	}
}
void sort_five(t_stack **a, t_stack **b)
{
	int size;
    
    size = stack_size(*a);
	if (size <= 3) 
	{
		sort_three(a);
		return;
	}
	sort_five_part1(a, b, size);
	sort_three(a);
	pa(a, b);
	if (size == 5)
		pa(a, b);
}

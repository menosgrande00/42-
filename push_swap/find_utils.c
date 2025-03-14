#include "push_swap.h"

int find_max_value(t_stack *stack)
{
	int max = INT_MIN;
	
	t_stack *tmp = stack;
	while (tmp) 
	{
		if (tmp->value > max)
			max = tmp->value;
		tmp = tmp->next;
	}
	return max;
}
int find_min_value(t_stack *stack)
{
	int min = INT_MAX;
	
	t_stack *tmp = stack;
	while (tmp) {
		if (tmp->value < min)
			min = tmp->value;
		tmp = tmp->next;
	}
	return min;
}
int find_max_index(t_stack *stack)
{
	int max = INT_MIN;
	int max_index = -1;
	int i = 0;
	
	t_stack *tmp = stack;
	while (tmp) 
	{
		if (tmp->value > max) 
		{
			max = tmp->value;
			max_index = i;
		}
		tmp = tmp->next;
		i++;
	}
	
	return max_index;
}
int find_min_index(t_stack *stack)
{
	int min = INT_MAX;
	int min_index = -1;
	int i = 0;
	
	t_stack *tmp = stack;
	while (tmp) 
	{
		if (tmp->value < min) 
		{
			min = tmp->value;
			min_index = i;
		}
		tmp = tmp->next;
		i++;
	}
	return (min_index);
}

#include "push_swap.h"
static t_stack	*ft_lstnew(int value)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void parse_args(t_stack **a, int argc, char **argv) 
{     
    t_stack *new_node;
    t_stack *last;
    int i;
    long num;

    i = 0;
    while (++i < argc)
    {
        char *arg = argv[i];
        if (!is_valid_number(arg)) 
            error_exit(a, NULL);
        num = ft_atoi(arg);
        if ((num < INT_MIN || num > INT_MAX) || is_duplicate(*a, (int)num)) 
            error_exit(a, NULL);
        new_node = ft_lstnew((int)num);
        if (*a == NULL) 
        {
            *a = new_node;
            last = *a;
        } 
        else 
        {
            last->next = new_node;
            last = last->next;
        }
    }
}

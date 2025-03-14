#include "push_swap.h"

int stack_size(t_stack *stack) 
{
    int size = 0;
    while (stack) 
    {
        size++;
        stack = stack->next;
    }
    return size;
}
int is_sorted(t_stack *stack) 
{
    if (!stack) 
        return 1;
    while (stack->next) 
    {
        if (stack->value > stack->next->value) 
            return 0;
        stack = stack->next;
    }
    return 1;
}
void free_stack(t_stack **stack) 
{
    t_stack *tmp;
    while (stack && *stack) 
    {
        tmp = *stack;
        *stack = (*stack)->next;
        free(tmp);
    }
    if (stack)
        *stack = NULL;
}

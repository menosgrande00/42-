#include "push_swap.h"

int main(int argc, char **argv) 
{
    t_stack *stack_a;
    t_stack *stack_b;

    stack_a = NULL;
    stack_b = NULL;

    if (argc < 2) 
    {
        write(2, "Error\n", 6);
        return (1);
    }
    parse_args(&stack_a, argc, argv);
    if (is_sorted(stack_a)) 
    {
        free_stack(&stack_a);
        return (0);
    }
    chunk_sort(&stack_a, &stack_b);
    while (stack_a != NULL)
    {
        printf("%d\n", stack_a->value);
        stack_a = stack_a->next;
    }
    free_stack(&stack_a);
    free_stack(&stack_b);
    return (0);
}

#include "push_swap.h"

int ft_atoi(const char *str) 
{
    long result = 0;
    int sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13)) 
        str++;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+') 
        str++;
    while (*str >= '0' && *str <= '9') 
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (int)(result * sign);
}

void error_exit(t_stack **a, t_stack **b) 
{
    free_stack(a);
    free_stack(b);
    write(2, "Error\n", 6);
    exit(1);
}
int ft_isdigit(int c) 
{
    return (c >= '0' && c <= '9');
}
int is_valid_number(char *str) 
{
    if (!str || !*str) 
        return (0);
    if (*str == '-' || *str == '+') 
        str++;
    while (*str) 
    {
        if (!ft_isdigit(*str)) 
            return (0);
        str++;
    }
    return 1;
}
int is_duplicate(t_stack *stack, int value) 
{
    while (stack) 
    {
        if (stack->value == value) 
            return (1);
        stack = stack->next;
    }
    return (0);
}

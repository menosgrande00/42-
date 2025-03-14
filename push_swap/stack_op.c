#include "push_swap.h"

void    sa(t_stack **a) 
{
    if (!*a || !(*a)->next) 
        return;
    t_stack *tmp = (*a)->next;
    (*a)->next = tmp->next;
    tmp->next = *a;
    *a = tmp;
    write(1, "sa\n", 3);
}

void    sb(t_stack **b) 
{
    if (!*b || !(*b)->next) 
        return;
    t_stack *tmp = (*b)->next;
    (*b)->next = tmp->next;
    tmp->next = *b;
    *b = tmp;
    write(1, "sb\n", 3);
}

void    ss(t_stack **a, t_stack **b) 
{
    sa(a);
    sb(b);
}

void    pa(t_stack **a, t_stack **b) 
{
    if (!*b) 
        return;
    t_stack *tmp = *b;
    *b = (*b)->next;
    tmp->next = *a;
    *a = tmp;
    write(1, "pa\n", 3);
}

void    pb(t_stack **a, t_stack **b) 
{
    if (!*a) 
        return;
    t_stack *tmp = *a;
    *a = (*a)->next;
    tmp->next = *b;
    *b = tmp;
    write(1, "pb\n", 3);
}

void ra(t_stack **a) 
{
    if (!*a || !(*a)->next) 
        return;
    t_stack *first = *a;
    *a = (*a)->next;
    t_stack *last = *a;
    while (last->next)
        last = last->next;
    last->next = first;
    first->next = NULL;
    write(1, "ra\n", 3);
}

void rb(t_stack **b) 
{
    if (!*b || !(*b)->next) 
        return;
    t_stack *first = *b;
    *b = (*b)->next;
    t_stack *last = *b;
    while (last->next) last = last->next;
    last->next = first;
    first->next = NULL;
    write(1, "rb\n", 3);
}

void    rr(t_stack **a, t_stack **b) 
{
    ra(a);
    rb(b);
}

void rra(t_stack **a) 
{
    if (!*a || !(*a)->next) 
        return;
    t_stack *prev = NULL;
    t_stack *last = *a;

    while (last->next) 
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    last->next = *a;
    *a = last;
    write(1, "rra\n", 4);
}

void    rrb(t_stack **b) 
{
    if (!*b || !(*b)->next) 
        return;
    t_stack *prev = NULL;
    t_stack *last = *b;
    while (last->next) 
    {
        prev = last;
        last = last->next;
    }
    prev->next = NULL;
    last->next = *b;
    *b = last;
    write(1, "rrb\n", 4);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:36:09 by oonal             #+#    #+#             */
/*   Updated: 2025/03/18 17:39:11 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include "stdio.h"

typedef struct s_stack {
	int				value;
	struct s_stack	*next;
}				t_stack;

void	sa(t_stack **a);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		is_valid_number(char *str);
int		is_duplicate(t_stack *stack, int value);
int		stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);
void	free_stack(t_stack **stack);
void	error_exit(t_stack **a, t_stack **b);

void	parse_args(t_stack **a, int argc, char **argv, int i);
void	sort_three(t_stack **a);
int		find_min_index(t_stack *stack);
void	sort_five_part1(t_stack **a, t_stack **b, int size);
void	sort_five(t_stack **a, t_stack **b);
int		find_max_index(t_stack *stack);
int		find_min_value(t_stack *stack);
int		find_max_value(t_stack *stack);
void	send_chunk_to_b(t_stack **a, t_stack **b, int lower, int upper);
void	send_max_to_a(t_stack **a, t_stack **b);
void	chunk_sort_part1(t_stack **a, t_stack **b);
void	chunk_sort(t_stack **a, t_stack **b);
char	**ft_split(char const *s, char c);

#endif
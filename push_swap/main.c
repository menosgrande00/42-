/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:20 by oonal             #+#    #+#             */
/*   Updated: 2025/03/18 19:21:02 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc < 2)
	{
		write (2, "Error\n", 6);
		return (1);
	}
	parse_args(&stack_a, argc, argv, 0);
	if (is_sorted(stack_a))
	{
		free_stack(&stack_a);
		return (0);
	}
	chunk_sort(&stack_a, &stack_b);

	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}

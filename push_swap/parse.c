/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:16 by oonal             #+#    #+#             */
/*   Updated: 2025/03/19 19:49:23 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	str_count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

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

void	process_elements(t_stack **a, char **argv, int argc, int i)
{
	t_stack	*new_node;
	t_stack	*last;
	long	num;
	char	*arg;

	last = NULL;
	while (++i < argc)
	{
		arg = argv[i];
		num = ft_atoi(arg);
		if (!is_valid_number(arg) || (num == 2147483649)
			|| is_duplicate(*a, num))
			error_exit(argv, a, NULL);
		new_node = ft_lstnew(num);
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

void	parse_args(t_stack **a, int argc, char **argv, int i)
{
	char	**split_args;
	int		split_count;
	int		j;

	if (argc == 2)
	{
		split_args = ft_split(argv[1], ' ');
		split_count = str_count(split_args);
		j = -1;
		process_elements(a, split_args, split_count, j);
		while (++j < split_count)
			free(split_args[j]);
		free(split_args);
	}
	else
		process_elements(a, argv, argc, i);
}

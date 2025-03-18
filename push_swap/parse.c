/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oonal <oonal@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:16 by oonal             #+#    #+#             */
/*   Updated: 2025/03/18 19:07:38 by oonal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	str_count(char **argv)
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

void	parse_args(t_stack **a, int argc, char **argv, int i)
{
	t_stack	*new_node;
	t_stack	*last;
	long	num;
	char	*arg;
	int		nbr;

	nbr = argc;
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		argc = str_count(argv);
		i--;
	}
	while (++i < argc)
	{
		arg = argv[i];
		num = ft_atoi(arg);
		if (!is_valid_number(arg) || (num < INT_MIN || num > INT_MAX)
			|| is_duplicate(*a, num))
			error_exit(a, NULL);
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
	i = 0;
	if (nbr == 2)
	{
		while (argv[i])
		{
			free(argv[i]);
			i++;
		}
		free(argv);
	}
}

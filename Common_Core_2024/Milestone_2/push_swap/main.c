/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:29:41 by igilani           #+#    #+#             */
/*   Updated: 2025/03/26 18:37:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	**handle_args(int argc, char **argv, bool *is_split)
{
	char	**args;

	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args || args[0] == NULL)
		{
			write(2, "Error\n", 6);
			free(args);
			return (NULL);
		}
		*is_split = true;
	}
	else
	{
		args = argv + 1;
		*is_split = false;
	}
	return (args);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**args;
	bool	is_split;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	args = handle_args(argc, argv, &is_split);
	if (!args)
		return (1);
	stack_init(&stack_a, args, is_split);
	if (!stack_sorted(stack_a))
	{
		if (ft_lstsize_push(stack_a) == 2)
			sa(&stack_a, false);
		else if (ft_lstsize_push(stack_a) == 3)
			tiny_sort(&stack_a);
		else
			push_swap(&stack_a, &stack_b);
	}
	if (is_split)
		free_matrix(args);
	free_stack(&stack_a);
}

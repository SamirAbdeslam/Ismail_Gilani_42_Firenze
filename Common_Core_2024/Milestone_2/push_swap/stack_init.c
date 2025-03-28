/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:57:54 by igilani           #+#    #+#             */
/*   Updated: 2025/03/28 16:44:00 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_init(t_stack **stack_a, char **argv, bool flag)
{
	long	nbr;
	int		i;

	*stack_a = NULL;
	i = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			error_handle(stack_a, argv, flag);
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_handle(stack_a, argv, flag);
		if (error_repetition(*stack_a, nbr))
			error_handle(stack_a, argv, flag);
		append_node(stack_a, (int)nbr);
		++i;
	}
	assign_final_index(*stack_a);
	(*stack_a)->cheapest = false;
}

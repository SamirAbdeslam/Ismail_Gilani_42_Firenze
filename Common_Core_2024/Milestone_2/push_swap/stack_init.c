/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:57:54 by igilani           #+#    #+#             */
/*   Updated: 2025/03/03 18:15:07 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_init(t_push_swap_stack **stack_a, char **argv, bool flag_argc_2)
{
	long long int		nbr;
	int 				i;

	i  = 0;
	while (argv[i] != NULL)
	{
		nbr = ft_atoll(argv[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			error_handle(stack_a, argv, flag_argc_2);
		if (error_repetition(*stack_a, nbr))
			error_handle(stack_a, argv, flag_argc_2);
		append_node(stack_a, (int)nbr);
		i++;
	}
}

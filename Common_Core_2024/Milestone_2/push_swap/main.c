/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:29:41 by igilani           #+#    #+#             */
/*   Updated: 2025/03/08 15:40:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char **argv)
{
	t_push_swap_stack	*stack_a;
	t_push_swap_stack	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if ( argc == 2)
		argv = ft_split(argv[1], ' ');
	stack_init(&stack_a, argv + 1, argc == 2);
	if (!stack_sorted(stack_a))
	{
		if (ft_lstsize_push(stack_a) == 2)
			sa(&stack_a, false);
		else if (ft_lstsize_push(stack_a) == 3)
			tiny_sort(&stack_a);
		else
			push_swap(&stack_a, &stack_b);
	}	
	ft_lstclear((t_list **)&stack_a, free);
}
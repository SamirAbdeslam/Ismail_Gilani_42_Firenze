/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:20:23 by igilani           #+#    #+#             */
/*   Updated: 2025/03/08 14:22:59 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rotate(t_push_swap_stack **stack)
{
	t_push_swap_stack *last_node;
	int len;

	len = ft_lstsize_push(*stack);
	if (*stack == NULL || stack == NULL || len == 1)
		return ;
	last_node = ft_lstlast_push(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next = NULL;
}

void ra (t_push_swap_stack **stack_a, bool checker)
{
	rotate(stack_a);
	if (!checker)
		write(1, "ra\n", 3);
}

void rb(t_push_swap_stack **stack_b, bool checker)
{
	rotate(stack_b);
	if (!checker)
		write(1, "rb\n", 3);
}

void rr(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker)
{
	rotate(stack_a);
	rotate(stack_b);
	if (!checker)
		write(1, "rr\n", 3);
}
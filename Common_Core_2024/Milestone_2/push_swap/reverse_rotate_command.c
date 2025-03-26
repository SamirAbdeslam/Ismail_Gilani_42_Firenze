/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:56:40 by igilani           #+#    #+#             */
/*   Updated: 2025/03/26 18:58:01 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack **stack)
{
	t_stack	*last_node;
	t_stack	*second_last_node;

	if (!stack || !(*stack) || !(*stack)->next)
		return ;
	last_node = *stack;
	while (last_node->next)
	{
		second_last_node = last_node;
		last_node = last_node->next;
	}
	second_last_node->next = NULL;
	last_node->next = *stack;
	*stack = last_node;
	if (last_node->next)
		last_node->next->prev = last_node;
}

void	rra(t_stack **stack_a, bool checker)
{
	reverse_rotate(stack_a);
	if (!checker)
		write(1, "rra\n", 4);
}

void	rrb(t_stack **stack_b, bool checker)
{
	reverse_rotate(stack_b);
	if (!checker)
		write(1, "rrb\n", 4);
}

void	rrr(t_stack **stack_a, t_stack **stack_b, bool checker)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	if (!checker)
		write(1, "rrr\n", 4);
}

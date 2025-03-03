/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:17:43 by igilani           #+#    #+#             */
/*   Updated: 2025/03/03 18:22:26 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_push_swap_stack **stack)
{
	int	len;

	len = ft_lstsize_push(*stack);
	if(*stack == NULL || stack == NULL || len == 1)
		return ;
	*stack = (*stack)->next;
	(*stack)->prev->next = (*stack)->next;
	if ((*stack)->next != NULL)
		(*stack)->next->prev = (*stack)->prev;
	(*stack)->next = (*stack)->prev;
	(*stack)->prev = NULL;
}

void sa(t_push_swap_stack **stack_a, bool checker)
{
	swap(stack_a);
	if(!checker)
		write(1, "sa\n", 3);
}

void sb(t_push_swap_stack **stack_b, bool checker)
{
	swap(stack_b);
	if(!checker)
		write(1, "sb\n", 3);
}

void ss(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker)
{
	swap(stack_a);
	swap(stack_b);
	if(!checker)
		write(1, "ss\n", 3);
}

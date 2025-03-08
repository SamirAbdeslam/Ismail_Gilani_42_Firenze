/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:56:33 by igilani           #+#    #+#             */
/*   Updated: 2025/03/08 17:42:48 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_push_swap_stack **dest, t_push_swap_stack **src)
{
	t_push_swap_stack	*node_to_push;

	if (NULL == *src)
		return ;
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_push->prev = NULL;
	if (NULL == *dest)
	{
		*dest = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dest;
		node_to_push->next->prev = node_to_push;
		*dest = node_to_push;
	}
}

void	pa(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker)
{
	push(stack_a, stack_b);
	if (!checker)
		write(1, "pa\n", 3);
}

void	pb(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker)
{
	push(stack_b, stack_a);
	if (!checker)
		write(1, "pb\n", 3);
}
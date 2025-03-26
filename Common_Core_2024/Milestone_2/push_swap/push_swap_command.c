/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:25:12 by igilani           #+#    #+#             */
/*   Updated: 2025/03/26 19:01:05 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	finish_rotation(t_stack **stack, t_stack *top_node, char stack_name)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}
	}
}

static void	move_nodes(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*cheapest_node;

	cheapest_node = return_cheapest(*stack_b);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(stack_a, stack_b, cheapest_node);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		reverse_rotate_both(stack_a, stack_b, cheapest_node);
	finish_rotation(stack_b, cheapest_node, 'b');
	finish_rotation(stack_a, cheapest_node->target_node, 'a');
	pa(stack_a, stack_b, false);
}

static void	last_push_swap(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*smallest;

	while (*stack_b)
	{
		init_nodes(*stack_a, *stack_b);
		move_nodes(stack_a, stack_b);
	}
	set_current_position(*stack_a);
	smallest = find_smallest(*stack_a);
	if (smallest->above_median)
	{
		while (*stack_a != smallest)
			ra(stack_a, false);
	}
	else
	{
		while (*stack_a != smallest)
			rra(stack_a, false);
	}
}

void	push_swap(t_stack **stack_a, t_stack **stack_b)
{
	int		len_a;

	len_a = ft_lstsize_push(*stack_a);
	if (len_a == 5)
		handle_five(stack_a, stack_b);
	else
	{
		while (len_a-- > 3)
		{
			if ((*stack_a)->above_median)
				pb(stack_a, stack_b, false);
			else
			{
				pb(stack_a, stack_b, false);
				rb(stack_b, false);
			}
		}
	}
	tiny_sort(stack_a);
	last_push_swap(stack_a, stack_b);
}

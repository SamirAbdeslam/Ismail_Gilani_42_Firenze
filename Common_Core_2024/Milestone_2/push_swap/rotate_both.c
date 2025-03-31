/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_both.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:43:51 by igilani           #+#    #+#             */
/*   Updated: 2025/03/31 14:21:31 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_both(t_stack **stack_a,
			t_stack **stack_b, t_stack *cheapest_node)
{
	while (*stack_a != cheapest_node->target_node && *stack_b != cheapest_node)
		rr(stack_a, stack_b, false);
	set_current_position(*stack_a);
	set_current_position(*stack_b);
}

void	reverse_rotate_both(t_stack **stack_a,
			t_stack **stack_b, t_stack *cheapest_node)
{
	while (*stack_a != cheapest_node->target_node && *stack_b != cheapest_node)
		rrr(stack_a, stack_b, false);
	set_current_position(*stack_a);
	set_current_position(*stack_b);
}

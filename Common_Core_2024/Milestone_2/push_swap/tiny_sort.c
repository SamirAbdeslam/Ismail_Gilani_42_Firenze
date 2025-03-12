/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:10:50 by igilani           #+#    #+#             */
/*   Updated: 2025/03/10 19:19:56 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool stack_sorted(t_push_swap_stack *stack)
{
    if (!stack)
        return (true);
        
    while (stack->next != NULL)
    {
        if (stack->value > stack->next->value)
            return (false);
        stack = stack->next;
    }
    return (true);
}

static t_push_swap_stack *find_highest(t_push_swap_stack *stack)
{
    t_push_swap_stack	*highest_node;
    int 				highest;

    if(stack == NULL)
        return (NULL);
    highest = INT_MIN;
    while (stack != NULL)
    {
        if (stack->value > highest)
        {
            highest = stack->value;
            highest_node = stack;
        }
        stack = stack->next;
    }
    return (highest_node);
}

// void tiny_sort(t_push_swap_stack **stack_a)
// {
// 	t_push_swap_stack *highest_node;

// 	highest_node = find_highest(*stack_a);
// 	if (*stack_a == highest_node)
// 		ra(stack_a, false);
// 	else if ((*stack_a)->value == highest_node->value)
// 		rra(stack_a, false);
// 	if((*stack_a)->value > highest_node->value)
// 		sa(stack_a, false);
// }

void	tiny_sort(t_push_swap_stack **a)
{
	t_push_swap_stack	*highest_node;

	highest_node = find_highest(*a);
	if (*a == highest_node)
		ra(a, false);
	else if ((*a)->next == highest_node)
		rra(a, false);
	if ((*a)->value > (*a)->next->value)
		sa(a, false);
}

void handle_five (t_push_swap_stack **stack_a, t_push_swap_stack **stack_b)
{
	while (ft_lstsize_push(*stack_a) > 3)
	{
		init_nodes(*stack_a, *stack_b);
		finish_rotation(stack_a, find_smallest(*stack_a), 'a');
		pb(stack_a, stack_b, false);
	}
}
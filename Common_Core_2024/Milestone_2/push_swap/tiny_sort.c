/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:10:50 by igilani           #+#    #+#             */
/*   Updated: 2025/03/25 16:33:51 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool stack_sorted(t_push_swap_stack *stack)
{
    if (!stack)
        return (true);
        
    while (stack->next != NULL)
    {
        if (stack->index > stack->next->index)
            return (false);
        stack = stack->next;
    }
    return (true);
}

static t_push_swap_stack *find_highest(t_push_swap_stack *stack)
{
    t_push_swap_stack *highest_node = NULL;
    int highest_index;

    if (!stack)
        return (NULL);
    
    highest_index = INT_MIN;
    while (stack)
    {
        if (stack->index > highest_index)
        {
            highest_index = stack->index;
            highest_node = stack;
        }
        stack = stack->next;
    }
    return (highest_node);
}

void tiny_sort(t_push_swap_stack **a)
{
    t_push_swap_stack *highest_node;

    highest_node = find_highest(*a);
    if (*a == highest_node)
        ra(a, false);
    else if ((*a)->next == highest_node)
        rra(a, false);
    if ((*a)->index > (*a)->next->index)
        sa(a, false);
}

void handle_five(t_push_swap_stack **a, t_push_swap_stack **b)
{
    while (ft_lstsize_push(*a) > 3)
    {
        init_nodes(*a, *b);
        finish_rotation(a, find_smallest(*a), 'a');
        pb(a, b, false);
    }
}

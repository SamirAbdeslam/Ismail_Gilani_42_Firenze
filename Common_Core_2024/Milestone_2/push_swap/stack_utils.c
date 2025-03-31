/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:33 by igilani           #+#    #+#             */
/*   Updated: 2025/03/31 14:03:34 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*ft_lstlast_push(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}

int	ft_lstsize_push(t_stack *stack)
{
	int	i;

	if (stack == NULL)
		return (0);
	i = 0;
	while (stack != NULL)
	{
		++i;
		stack = stack->next;
	}
	return (i);
}

void	append_node(t_stack **stack, int nbr)
{
	t_stack	*node;
	t_stack	*last_node;

	node = malloc(sizeof(t_stack));
	if (node == NULL)
		return ;
	node->value = nbr;
	node->next = NULL;
	node->prev = NULL;
	node->index = 0;
	node->current_position = 0;
	node->push_price = 0;
	node->cheapest = false;
	node->above_median = false;
	node->target_node = NULL;
	if (*stack == NULL)
		*stack = node;
	else
	{
		last_node = ft_lstlast_push(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

t_stack	*find_smallest(t_stack *stack)
{
	t_stack	*smallest_node;
	int		smallest_index;

	smallest_node = NULL;
	if (!stack)
		return (NULL);
	smallest_index = INT_MAX;
	while (stack)
	{
		if (stack->index < smallest_index)
		{
			smallest_index = stack->index;
			smallest_node = stack;
		}
		stack = stack->next;
	}
	return (smallest_node);
}

t_stack	*return_cheapest(t_stack *stack)
{
	if (stack == NULL)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

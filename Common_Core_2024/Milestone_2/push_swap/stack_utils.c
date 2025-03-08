/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:12:45 by igilani           #+#    #+#             */
/*   Updated: 2025/03/08 14:29:31 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_push_swap_stack	*ft_lstlast_push(t_push_swap_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	append_node(t_push_swap_stack **stack, int nbr)
{
	t_push_swap_stack	*node;
	t_push_swap_stack	*last_node;

	if (stack == NULL)
		return ;
	node = malloc(sizeof(t_push_swap_stack));
	if (node == NULL)
		return;
	node->next = NULL;
	node->value = nbr;
	if (*stack == NULL)
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = ft_lstlast_push(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

t_push_swap_stack	*find_smallest(t_push_swap_stack *stack)
{
	long	smallest;
	t_push_swap_stack	*smallest_node;

	if (stack == NULL)
		return (NULL);
	smallest = LONG_MAX;
	while (stack)
	{
		if (stack->value < smallest)
		{
			smallest = stack->value;
			smallest_node = stack;
		}
		stack = stack->next;
	}
	return (smallest_node);
}

t_push_swap_stack	*return_cheapest(t_push_swap_stack *stack)
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

int	ft_lstsize_push(t_push_swap_stack *stack)
{
	int		i;

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
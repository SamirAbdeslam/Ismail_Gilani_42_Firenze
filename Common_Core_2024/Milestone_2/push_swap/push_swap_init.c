/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   push_swap_init.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igilani <igilani@student.42firenze.it>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/03 18:35:39 by igilani		   #+#	#+#			 */
/*   Updated: 2025/03/26 17:51:27 by igilani		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "push_swap.h"

void	set_current_position(t_stack *stack)
{
	int	i;
	int	centerline;

	i = 0;
	if (stack == NULL)
		return ;
	centerline = ft_lstsize_push(stack) / 2;
	while (stack != NULL)
	{
		stack->current_position = i;
		if (i <= centerline)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		++i;
	}
}

static void	set_target_node(t_stack *stack_a, t_stack *stack_b)
{
	t_stack	*current_a;
	t_stack	*target_node;
	long	best_match_index;

	while (stack_b != NULL)
	{
		best_match_index = LONG_MAX;
		current_a = stack_a;
		while (current_a != NULL)
		{
			if (current_a->value > stack_b->value
				&& current_a->value < best_match_index)
			{
				best_match_index = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (LONG_MAX == best_match_index)
			stack_b->target_node = find_smallest(stack_a);
		else
			stack_b->target_node = target_node;
		stack_b = stack_b->next;
	}
}

void	set_price(t_stack *stack_a, t_stack *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = ft_lstsize_push(stack_a);
	len_b = ft_lstsize_push(stack_b);
	while (stack_b != NULL)
	{
		stack_b->push_price = stack_b->current_position;
		if (!(stack_b->above_median))
			stack_b->push_price = len_b - (stack_b->current_position);
		if (stack_b->target_node->above_median)
			stack_b->push_price += stack_b->target_node->current_position;
		else
			stack_b->push_price += len_a - stack_b
				->target_node->current_position;
		stack_b = stack_b->next;
	}
}

void	set_cheapest(t_stack *stack_b)
{
	long int	best_match_value;
	t_stack		*best_match_node;

	if (stack_b == NULL)
		return ;
	best_match_value = LONG_MAX;
	while (stack_b != NULL)
	{
		if (stack_b->push_price < best_match_value)
		{
			best_match_value = stack_b->push_price;
			best_match_node = stack_b;
		}
		stack_b = stack_b->next;
	}
	best_match_node->cheapest = true;
}

void	init_nodes(t_stack *stack_a, t_stack *stack_b)
{
	set_current_position(stack_a);
	set_current_position(stack_b);
	set_target_node(stack_a, stack_b);
	set_price(stack_a, stack_b);
	set_cheapest(stack_b);
}

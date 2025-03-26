/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   rotate_command.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: igilani <igilani@student.42firenze.it>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/08 14:20:23 by igilani		   #+#	#+#			 */
/*   Updated: 2025/03/26 17:54:44 by igilani		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_stack **stack)
{
	int		len;
	t_stack	*first_node;
	t_stack	*last_node;

	len = ft_lstsize_push(*stack);
	if (*stack == NULL || stack == NULL || len == 1)
		return ;
	first_node = *stack;
	last_node = ft_lstlast_push(*stack);
	*stack = first_node->next;
	(*stack)->prev = NULL;
	last_node->next = first_node;
	first_node->prev = last_node;
	first_node->next = NULL;
}

void	ra(t_stack **stack_a, bool checker)
{
	rotate(stack_a);
	if (!checker)
		write(1, "ra\n", 3);
}

void	rb(t_stack **stack_b, bool checker)
{
	rotate(stack_b);
	if (!checker)
		write(1, "rb\n", 3);
}

void	rr(t_stack **stack_a, t_stack **stack_b, bool checker)
{
	rotate(stack_a);
	rotate(stack_b);
	if (!checker)
		write(1, "rr\n", 3);
}

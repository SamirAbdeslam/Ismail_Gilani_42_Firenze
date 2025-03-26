/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:09:09 by igilani           #+#    #+#             */
/*   Updated: 2025/03/25 19:44:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void free_stack(t_push_swap_stack **stack)
{
    t_push_swap_stack *tmp;

    if (!stack || !(*stack))
        return;
    
    while (*stack)
    {
        tmp = (*stack)->next;
        free(*stack);
        *stack = tmp;
    }
}

void	free_matrix(char **argv)
{
	int	i;

	i = -1;
	if (NULL == argv || NULL == *argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv - 1);
}

void	error_handle(t_push_swap_stack **stack_a, char **argv, bool flag)
{
	ft_lstclear((t_list **)stack_a, free);
	if (flag)
		ft_lstclear((t_list **)argv, free);
	write(2, "Error\n", 6);
	exit(1);
}

int	error_syntax(char *str)
{
	if (!(*str))
		return (0);
	if (!(*str == '+' || *str == '-' || ft_isdigit(*str)))
		return (1);
	if ((*str == '+' || *str == '-') && !ft_isdigit(*(str + 1)))
		return (1);
	while (*++str)
	{
		if (!ft_isdigit(*str))
			return (1);
	}
	return (0);
}

int error_repetition(t_push_swap_stack *stack_a, int nbr)
{
	if(stack_a == NULL)
		return (0);
	while (stack_a != NULL)
	{
		if (stack_a->value == nbr)
			return (1);
		stack_a = stack_a->next;
	}
	return (0);
}
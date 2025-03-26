/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:09:09 by igilani           #+#    #+#             */
/*   Updated: 2025/03/26 15:44:00 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_matrix(char **argv)
{
	int	i;

	i = 0;
	if (!argv || !*argv)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}

void free_stack(t_push_swap_stack **stack)
{
    t_push_swap_stack *tmp;
	t_push_swap_stack *current;

    if (!stack || !(*stack))
        return;
    current = *stack;
    while (current)
    {
        tmp = current->next;
        free(current);
        current = tmp;
    }
	*stack = NULL;
}

void	error_handle(t_push_swap_stack **a, char **argv, bool flag)
{
	if (a)
		free_stack(a);
	if (flag)
		free_matrix(argv);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	error_syntax(char *str)
{
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
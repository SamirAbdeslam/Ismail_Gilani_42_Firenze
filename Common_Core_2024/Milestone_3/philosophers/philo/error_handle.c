/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:04:47 by igilani           #+#    #+#             */
/*   Updated: 2025/04/07 18:21:44 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

// void	free_stack(t_stack **stack)
// {
// 	t_stack	*tmp;
// 	t_stack	*current;

// 	if (!stack || !(*stack))
// 		return ;
// 	current = *stack;
// 	while (current)
// 	{
// 		tmp = current->next;
// 		free(current);
// 		current = tmp;
// 	}
// 	*stack = NULL;
// }

void	error_handle(char *error_message)
{
	printf("Error: %s\n", error_message);
	exit(EXIT_FAILURE);
}

int	error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-' || ft_isdigit(*str)))
		return (1);
	if (*str == '-')
		return (1);
	while (*++str)
	{
		if (!ft_isdigit(*str))
			return (1);
	}
	return (0);
}

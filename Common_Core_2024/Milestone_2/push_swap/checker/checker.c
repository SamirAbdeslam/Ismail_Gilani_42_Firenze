/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:55:39 by igilani           #+#    #+#             */
/*   Updated: 2025/03/27 17:37:26 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void handle_error()
{
	write(1, "Error\n", 6);
	exit(1);
}

static void parsing(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (!ft_strncmp(command, "pa\n", 3))
		pa(stack_a, stack_b, false);
	else if (!ft_strncmp(command, "pb\n", 3))
		pb(stack_a, stack_b, false);
	else if (!ft_strncmp(command, "sa\n", 3))
		sa(stack_a, false);
	else if (!ft_strncmp(command, "sb\n", 3))
		sb(stack_b, false);
	else if (!ft_strncmp(command, "ss\n", 3))
		ss(stack_a, stack_b, false);
	else if (!ft_strncmp(command, "ra\n", 3))
		ra(stack_a, false);
	else if (!ft_strncmp(command, "rb\n", 3))
		rb(stack_b, false);
	else if (!ft_strncmp(command, "rr\n", 3))
		rr(stack_a, stack_b, false);
	else if (!ft_strncmp(command, "rra\n", 4))
		rra(stack_a, false);
	else if (!ft_strncmp(command, "rrb\n", 4))
		rrb(stack_b, false);
	else if (!ft_strncmp(command, "rrr\n", 4))
		rrr(stack_a, stack_b, false);
	else
		handle_error();
}

int main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		len;
	char	*next_line;
	bool	is_split = false;
	
	stack_a = NULL;
	stack_b = NULL;
	len = 0;
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		ft_split(argv[1], ' ');
		is_split = true;
	}
	else
	{
		argv++;
		is_split = false;
	}
	len = ft_lstsize_push(stack_a);
	stack_init(&stack_a, argv, is_split);
	next_line = get_next_line(STDIN_FILENO);
	while (next_line)
	{
		parsing(&stack_a, &stack_b, next_line);
		next_line = get_next_line(STDIN_FILENO);
	}
	if (stack_sorted(stack_a) && ft_lstsize_push(stack_a) == len)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	if (is_split)
		free_matrix(argv);
	free_stack(&stack_a);
}
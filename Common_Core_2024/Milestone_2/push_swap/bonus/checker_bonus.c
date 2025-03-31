/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:58:26 by igilani           #+#    #+#             */
/*   Updated: 2025/03/31 13:55:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void	handle_error(t_stack **stack_a, t_stack **stack_b, char *command)
{
	free_stack(stack_a);
	free_stack(stack_b);
	free(command);
	write(1, "Error\n", 6);
	exit(1);
}

static void	parsing(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (!ft_strncmp(command, "pa\n", 3))
		pa(stack_a, stack_b, true);
	else if (!ft_strncmp(command, "pb\n", 3))
		pb(stack_a, stack_b, true);
	else if (!ft_strncmp(command, "sa\n", 3))
		sa(stack_a, true);
	else if (!ft_strncmp(command, "sb\n", 3))
		sb(stack_b, true);
	else if (!ft_strncmp(command, "ss\n", 3))
		ss(stack_a, stack_b, true);
	else if (!ft_strncmp(command, "ra\n", 3))
		ra(stack_a, true);
	else if (!ft_strncmp(command, "rb\n", 3))
		rb(stack_b, true);
	else if (!ft_strncmp(command, "rr\n", 3))
		rr(stack_a, stack_b, true);
	else if (!ft_strncmp(command, "rra\n", 4))
		rra(stack_a, true);
	else if (!ft_strncmp(command, "rrb\n", 4))
		rrb(stack_b, true);
	else if (!ft_strncmp(command, "rrr\n", 4))
		rrr(stack_a, stack_b, true);
	else
		handle_error(stack_a, stack_b, command);
	free(command);
}

char	**handle_args(int argc, char **argv, bool *is_split)
{
	char	**args;

	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args || args[0] == NULL)
		{
			write(2, "Erron\n", 6);
			free(args);
			return (NULL);
		}
		*is_split = true;
	}
	else
	{
		args = argv + 1;
		*is_split = false;
	}
	return (args);
}

static void	process_commands(t_stack **stack_a, t_stack **stack_b)
{
	int		len;
	char	*next_line;

	len = ft_lstsize_push(*stack_a);
	next_line = get_next_line(STDIN_FILENO);
	while (next_line)
	{
		parsing(stack_a, stack_b, next_line);
		next_line = get_next_line(STDIN_FILENO);
	}
	if (stack_sorted(*stack_a) && ft_lstsize_push(*stack_a) == len)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	**args;
	bool	is_split;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	args = handle_args(argc, argv, &is_split);
	if (!args)
		return (1);
	stack_init(&stack_a, args, is_split);
	if (is_split)
		free_matrix(args);
	process_commands(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
}

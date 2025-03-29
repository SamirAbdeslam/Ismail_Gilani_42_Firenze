/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:55:39 by igilani           #+#    #+#             */
/*   Updated: 2025/03/29 10:58:51 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void print_stack(t_stack *stack)
{
    while (stack)
    {
        printf("%d ", stack->value);
        stack = stack->next;
    }
    printf("\n");
}
/*
static void result_message(t_stack *stack, t_stack **stack_a, t_stack **stack_b)
{
	print_stack(*stack_a);
	if (stack_sorted(stack))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(stack_a);
	free_stack(stack_b);
}
*/
static void handle_error(t_stack **stack_a, t_stack **stack_b, char *command)
{
	free_stack(stack_a);
	free_stack(stack_b);
	free(command);
	write(1, "Error\n", 6);
	exit(1);
}
/*
static char	**args_handle(int argc, char **argv)
{
	char	**args;
	
	if (argc == 2)
	{
		args = ft_split(argv[1], ' ');
		if (!args || args[0] == NULL)
		{
			handle_error(NULL, NULL, *args);
			return (NULL);
		}
	}
	else
		args = argv + 1;
	return (args);
}
*/
static void parsing(t_stack **stack_a, t_stack **stack_b, char *command)
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

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char			*next_line;
	int				len;
	char			**args = NULL;

	stack_a = NULL;
	stack_b = NULL;
	if (1 == argc)
		return (0);
	else if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv + 1;
	if (!args || args[0] == NULL || error_syntax(args[0]))
	{
		free_matrix(args);
		handle_error(NULL, NULL, NULL);
	}
	stack_init(&stack_a, args, 2 == argc);
	len = ft_lstsize_push(stack_a);
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
	if (argc == 2)
		free_matrix(args);
	free_stack(&stack_a);
	free_stack(&stack_b);
}
/*
int main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	*next_line;
	//char	**args;

	stack_a = NULL;
	stack_b = NULL;
	//args = NULL;
	if (argc == 1)
		return (0);
	if (argc == 2)
		argv = ft_split(argv[1], ' ');
	//if (!args || args[0] == NULL)
	//	handle_error(&stack_a, &stack_b, NULL);
	stack_init(&stack_a, argv + 1, false);
	next_line = get_next_line(STDIN_FILENO);
	while (next_line)
	{
		parsing(&stack_a, &stack_b, next_line);
		next_line = get_next_line(STDIN_FILENO);
	}
	result_message(stack_a, &stack_a, &stack_b);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:58:26 by igilani           #+#    #+#             */
/*   Updated: 2025/03/28 19:44:20 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static void result_message(t_stack *stack, t_stack **stack_a, t_stack **stack_b)
{
	if (stack_sorted(stack))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(stack_a);
	free_stack(stack_b);
}

static void handle_error(t_stack **stack_a, t_stack **stack_b, char *command)
{
	if (stack_a)
		free_stack(stack_a);
	if (stack_b)
		free_stack(stack_b);
	if (command)
		free(command);
	write(1, "Error\n", 6);
	exit(1);
}

static char	**args_handle(int argc, char **argv)
{
	char	**args;
	int		i;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
		args = argv + 1;
	return (args);
}

static void parsing(int argc, char **argv, t_stack **stack_a)
{
	int		i;
	long	nbr;
	char 	**args;

	i = 0;
	nbr = 0;
	while (argv[i])
	{
		if (error_syntax(argv[i]))
			handle_error(stack_a, NULL, NULL);
		nbr = ft_atol(args[i]);
		if (nbr > INT_MAX || nbr < INT_MIN)
			handle_error(stack_a, NULL, NULL);
		if (error_repetition(*stack_a, nbr))
			handle_error(stack_a, NULL, NULL);
		args = args_handle(argc, argv);
		append_node(stack_a, (int)nbr);
		++i;
	}
}

static void check_moves(t_stack **stack_a, t_stack **stack_b, char *command)
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

void print_stack(t_stack *stack)
{
    while (stack)
    {
        printf("%d ", stack->value);
        stack = stack->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	char	*next_line;
	// char	**args;
	// long	nbr;

	stack_a = NULL;
	stack_b = NULL;
	// args = NULL;

	if (argc == 1)
		return (0);
	parsing(argc, argv + 1, &stack_a);
	// args = args_handle(argc, argv);
	// if (!args || args[0] == NULL)
	// 	handle_error(&stack_a, &stack_b, *args);

	    printf("Stack A iniziale: ");
    print_stack(stack_a);

    next_line = get_next_line(STDIN_FILENO);
    while (next_line)
    {
        check_moves(&stack_a, &stack_b, next_line);
        printf("Stack A: ");
        print_stack(stack_a);
        printf("Stack B: ");
        print_stack(stack_b);
        next_line = get_next_line(STDIN_FILENO);
    }

    printf("Stack A finale: ");
    print_stack(stack_a);
    printf("Stack B finale: ");
    print_stack(stack_b);
	
	// next_line = get_next_line(STDIN_FILENO);
	// while (next_line)
	// {
	// 	check_moves(&stack_a, &stack_b, next_line);
	// 	next_line = get_next_line(STDIN_FILENO);
	// }
	result_message(stack_a, &stack_a, &stack_b);
}

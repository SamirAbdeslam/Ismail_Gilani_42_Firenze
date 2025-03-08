/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:29:41 by igilani           #+#    #+#             */
/*   Updated: 2025/03/08 17:39:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char **argv)
{
    t_push_swap_stack	*stack_a;
    t_push_swap_stack	*stack_b;
    char				**args;
    bool				is_split;

    stack_a = NULL;
    stack_b = NULL;
    if (argc == 1 || (argc == 2 && !argv[1][0]))
        return (1);
    if (argc == 2)
    {
        args = ft_split(argv[1], ' ');
        if (!args)
            return (1);
        is_split = true;
    }
    else
    {
        args = argv + 1;
        is_split = false;
    }
    stack_init(&stack_a, args, is_split);
    if (!stack_sorted(stack_a))
    {
        if (ft_lstsize_push(stack_a) == 2)
            sa(&stack_a, false);
        else if (ft_lstsize_push(stack_a) == 3)
            tiny_sort(&stack_a);
        else
            push_swap(&stack_a, &stack_b);
    }
	free_stack(&stack_a);
	free_stack(&stack_b);
    if (is_split)
    {
        int i = 0;
        while (args[i])
            free(args[i++]);
        free(args);
    }
    return (0);
}
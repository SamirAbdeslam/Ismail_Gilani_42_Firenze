/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:27:46 by igilani           #+#    #+#             */
/*   Updated: 2025/03/03 18:57:29 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include "tha_supreme_lib/tha_supreme_lib.h"

typedef struct s_push_swap_stack
{
	int							value;
	int							current_position;
	int							final_index;
	int							push_price;
	bool						above_median;
	bool						cheapest;
	struct s_push_swap_stack	*target_node;
	struct s_push_swap_stack	*next;
	struct s_push_swap_stack	*prev;
} 			t_push_swap_stack;

/* Stack Init */
void	stack_init(t_push_swap_stack **stack_a, char **argv, bool flag_argc_2);

/* Stack Operations */
void	sa(t_push_swap_stack **stack_a, bool checker);
void	sb(t_push_swap_stack **stack_b, bool checker);
void	ss(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker);

/* Stack Utils */
int		ft_lstsize_push(t_push_swap_stack *stack);
t_push_swap_stack	*ft_lstlast_push(t_push_swap_stack *lst);
void	append_node(t_push_swap_stack **stack, int nbr);

/* Push Swap */
void	push_swap(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b);
void	handle_five(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b);
void	set_current_position(t_push_swap_stack *stack);
void	set_price(t_push_swap_stack *stack_a, t_push_swap_stack *stack_b);
void 	set_target_node(t_push_swap_stack *stack_a, t_push_swap_stack *stack_b);
t_push_swap_stack	*find_smallest(t_push_swap_stack *stack);
void	init_nodes(t_push_swap_stack *stack_a, t_push_swap_stack *stack_b);
void tiny_sort(t_push_swap_stack **stack_a);
bool stack_sorted(t_push_swap_stack *stack);

/* Erorr Handle */
int error_repetition(t_push_swap_stack *stack_a, int nbr);
void error_handle(t_push_swap_stack **stack_a, char **argv, bool flag_argc_2);
#endif
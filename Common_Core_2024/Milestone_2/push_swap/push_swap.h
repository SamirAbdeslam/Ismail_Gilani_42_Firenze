/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:27:46 by igilani           #+#    #+#             */
/*   Updated: 2025/03/08 18:17:21 by igilani          ###   ########.fr       */
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
void	set_current_position(t_push_swap_stack *stack);
void	set_price(t_push_swap_stack *stack_a, t_push_swap_stack *stack_b);
void	init_nodes(t_push_swap_stack *stack_a, t_push_swap_stack *stack_b);
void	set_cheapest(t_push_swap_stack *stack);

/* Stack Utils */
void				append_node(t_push_swap_stack **stack, int nbr);
int					ft_lstsize_push(t_push_swap_stack *stack);
bool 				stack_sorted(t_push_swap_stack *stack);
t_push_swap_stack	*ft_lstlast_push(t_push_swap_stack *lst);
t_push_swap_stack	*find_smallest(t_push_swap_stack *stack);
t_push_swap_stack	*return_cheapest(t_push_swap_stack *stack);
void				finish_rotation(t_push_swap_stack **stack, t_push_swap_stack *top_node, char stack_name);

/* Algorithms */
void	tiny_sort(t_push_swap_stack **stack_a);
void	handle_five(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b);
void	push_swap(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b);

/* Commands */
void	sa(t_push_swap_stack **stack_a, bool checker);
void	sb(t_push_swap_stack **stack_b, bool checker);
void	ss(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker);
void 	ra (t_push_swap_stack **stack_a, bool checker);
void 	rb(t_push_swap_stack **stack_b, bool checker);
void 	rr(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker);
void	rra(t_push_swap_stack **stack_a, bool checker);
void	rrb(t_push_swap_stack **stack_b, bool checker);
void 	rrr(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker);
void	pa(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker);
void	pb(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, bool checker);

/* Erorr Handle */
void	free_matrix(char **argv);
int		error_syntax(char *str);
int 	error_repetition(t_push_swap_stack *stack_a, int nbr);
void 	error_handle(t_push_swap_stack **stack_a, char **argv, bool flag_argc_2);
void 	free_stack(t_push_swap_stack **stack);


void optimize_rotations(t_push_swap_stack **stack_a, t_push_swap_stack **stack_b, int cost_a, int cost_b);
#endif
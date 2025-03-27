/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:27:46 by igilani           #+#    #+#             */
/*   Updated: 2025/03/27 16:34:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include "tha_supreme_lib/tha_supreme_lib.h"

typedef struct s_stack
{
	int				value;
	int				current_position;
	int				push_price;
	int				index;
	bool			above_median;
	bool			cheapest;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}			t_stack;

/* Stack Init */
void	stack_init(t_stack **stack_a, char **argv, bool flag);
void	set_current_position(t_stack *stack);
void	set_price(t_stack *stack_a, t_stack *stack_b);
void	init_nodes(t_stack *stack_a, t_stack *stack_b);
void	set_cheapest(t_stack *stack);
void	assign_final_index(t_stack *stack);
char	**handle_args(int argc, char **argv, bool *is_split);

/* Stack Utils */
void	append_node(t_stack **stack, int nbr);
void	finish_rotation(t_stack **stack, t_stack *top_node, char stack_name);
int		ft_lstsize_push(t_stack *stack);
bool	stack_sorted(t_stack *stack);
t_stack	*ft_lstlast_push(t_stack *lst);
t_stack	*find_smallest(t_stack *stack);
t_stack	*return_cheapest(t_stack *stack);

/* Algorithms */
void	tiny_sort(t_stack **stack_a);
void	handle_five(t_stack **stack_a, t_stack **stack_b);
void	push_swap(t_stack **stack_a, t_stack **stack_b);

/* Commands */
void	sa(t_stack **stack_a, bool checker);
void	sb(t_stack **stack_b, bool checker);
void	ss(t_stack **stack_a, t_stack **stack_b, bool checker);
void	ra(t_stack **stack_a, bool checker);
void	rb(t_stack **stack_b, bool checker);
void	rr(t_stack **stack_a, t_stack **stack_b, bool checker);
void	rra(t_stack **stack_a, bool checker);
void	rrb(t_stack **stack_b, bool checker);
void	rrr(t_stack **stack_a, t_stack **stack_b, bool checker);
void	pa(t_stack **stack_a, t_stack **stack_b, bool checker);
void	pb(t_stack **stack_a, t_stack **stack_b, bool checker);
void	rotate_both(t_stack **stack_a,
			t_stack **stack_b, t_stack *cheapest_node);
void	reverse_rotate_both(t_stack **stack_a,
			t_stack **stack_b, t_stack *cheapest_node);

/* Erorr Handle */
void	free_matrix(char **argv);	
int		error_syntax(char *str);
int		error_repetition(t_stack *stack_a, int nbr);
void	error_handle(t_stack **stack_a, char **argv, bool flag);
void	free_stack(t_stack **stack);

#endif
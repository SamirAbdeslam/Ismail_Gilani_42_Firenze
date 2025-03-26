/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:17:30 by igilani           #+#    #+#             */
/*   Updated: 2025/03/26 18:55:37 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bubble_sort(int *values, int len)
{
	int	j;
	int	k;
	int	temp;

	j = 0;
	while (j < len - 1)
	{
		k = 0;
		while (k < len - j - 1)
		{
			if (values[k] > values[k + 1])
			{
				temp = values[k];
				values[k] = values[k + 1];
				values[k + 1] = temp;
			}
			k++;
		}
		j++;
	}
}

int	find_median(t_stack *stack)
{
	t_stack	*current;
	int		len;
	int		*values;
	int		i;
	int		median;

	len = ft_lstsize_push(stack);
	values = malloc(len * sizeof(int));
	if (!values)
		return (0);
	current = stack;
	i = 0;
	while (current != NULL)
	{
		values[i++] = current->value;
		current = current->next;
	}
	bubble_sort(values, len);
	median = values[len / 2];
	free(values);
	return (median);
}

void	assign_final_index(t_stack *stack)
{
	t_stack	*current;
	t_stack	*compare;
	int		median;

	median = find_median(stack);
	current = stack;
	while (current != NULL)
	{
		current->index = 0;
		current->above_median = (current->value > median);
		compare = stack;
		while (compare != NULL)
		{
			if (compare->value < current->value)
				current->index++;
			compare = compare->next;
		}
		current = current->next;
	}
}

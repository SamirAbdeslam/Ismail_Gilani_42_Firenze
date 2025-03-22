/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:17:30 by igilani           #+#    #+#             */
/*   Updated: 2025/03/22 14:48:41 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			ft_swap(&arr[i], &arr[j]);
		}
		j++;
	}
	ft_swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	ft_quick_sort(int *arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		ft_quick_sort(arr, low, pi - 1);
		ft_quick_sort(arr, pi + 1, high);
	}
}

void	assign_final_index(t_push_swap_stack *stack)
{
	t_push_swap_stack	*tmp;
	int					*sorted_values;
	int					size;
	int					i;

	if (!stack)
		return;
	size = ft_lstsize_push(stack);
	sorted_values = malloc(size * sizeof(int));
	tmp = stack;
	i = 0;
	while (tmp)
	{
		sorted_values[i++] = tmp->value;
		tmp = tmp->next;
	}
	ft_quick_sort(sorted_values, 0, size - 1);
	tmp = stack;
	while (tmp)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->value == sorted_values[i])
			{
				tmp->final_index = i;
				break;
			}
			i++;
		}
		tmp = tmp->next;
	}
	free(sorted_values);
}
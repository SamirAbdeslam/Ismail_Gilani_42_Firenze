/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:17:30 by igilani           #+#    #+#             */
/*   Updated: 2025/03/25 16:33:28 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int find_median(t_push_swap_stack *stack)
{
    int len = ft_lstsize_push(stack);
    int *values = malloc(len * sizeof(int));
    t_push_swap_stack *current = stack;
    int i = 0;

    while (current != NULL)
    {
        values[i++] = current->value;
        current = current->next;
    }
    int j = 0;
    while (j < len - 1)
    {
        int k = 0;
        while (k < len - j - 1)
        {
            if (values[k] > values[k + 1])
            {
                int temp = values[k];
                values[k] = values[k + 1];
                values[k + 1] = temp;
            }
            k++;
        }
        j++;
    }
    int median = values[len / 2];
    free(values);
    return median;
}

void assign_final_index(t_push_swap_stack *stack)
{
    t_push_swap_stack *current;
    t_push_swap_stack *compare;
    int median = find_median(stack);

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

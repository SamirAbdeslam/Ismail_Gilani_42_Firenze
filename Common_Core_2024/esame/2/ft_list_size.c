/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:00:22 by igilani           #+#    #+#             */
/*   Updated: 2025/03/19 11:16:58 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct    s_list
{
    struct s_list *next;
    void          *data;
}                 t_list;

int	ft_list_size(t_list *begin_list)
{
	int i = 1;

	if (!begin_list)
		return(0);
	while(begin_list->next)
	{
		begin_list = begin_list->next;
		i++;
	}
	return(i);
}

int	main(void)
{
	int n = 0;

	t_list *c = malloc(sizeof(*c));
	c->next = 0;
	c->data = &n;

	t_list *b = malloc(sizeof(*b));
	b->next = c;
	b->data = &n;

	t_list *a = malloc(sizeof(*a));
	a->next = 0;
	a->data = &n;

	printf("%d\n", ft_list_size(a));
}
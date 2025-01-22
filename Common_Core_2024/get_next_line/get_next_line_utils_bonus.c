/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:20:13 by igilani           #+#    #+#             */
/*   Updated: 2025/01/22 15:13:46 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_lstchr(t_list *lst)
{
	int	i;

	if (NULL == lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->str_buffer[i] && i < BUFFER_SIZE)
		{
			if (lst->str_buffer[i] == '\n')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst -> next;
	}
	return (lst);
}

int	ft_lstlen(t_list *lst)
{
	int	i;
	int	len;

	if (lst == NULL)
		return (0);
	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buffer[i])
		{
			if (lst->str_buffer[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_lstdup(t_list *lst, char *str)
{
	int	i;
	int	k;

	if (lst == NULL)
		return ;
	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->str_buffer[i])
		{
			if (lst->str_buffer[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = lst->str_buffer[i++];
		}
		lst = lst->next;
	}
	str[k] = '\0';
}

void	ft_lstfree(t_list **lst, t_list *clean_node, char *buffer)
{
	t_list	*tmp;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->str_buffer);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
	if (clean_node->str_buffer[0])
	{
		*lst = clean_node;
	}
	else
	{
		free(buffer);
		free(clean_node);
	}
}

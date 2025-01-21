/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:20:13 by igilani           #+#    #+#             */
/*   Updated: 2025/01/21 19:38:21 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*char	*ft_strchr(t_list *lst)
{
	int				i;

	i = 0;
	while (lst)
	{
		while(lst->str_buffer[i])
		{
			if (lst->str_buffer[i] == '\n')
			{
				return ((char *)&lst->str_buffer[i]);
			}
			i++;
		}
		lst = lst->next;
	}
	return (NULL);
}*/

int	ft_strchr(t_list *lst)
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

/*void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	unsigned char	*str;
	size_t			i;

	mem = malloc(nmemb * size);
	if (!mem)
		return (NULL);
	str = (unsigned char *)mem;
	i = 0;
	while (i < nmemb * size)
	{
		str[i] = '\0';
		i++;
	}
	return (mem);
}*/

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
		return;
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
				return;
			}
			str[k++] = lst->str_buffer[i++];
		}
		lst = lst->next;
	}
	str[k] = '\0';
}

void	ft_free(t_list **lst, t_list *clean_node, char *buffer)
{
	t_list	*tmp;

	if(lst == NULL)
		return;
	while(*lst)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:20:09 by igilani           #+#    #+#             */
/*   Updated: 2025/01/21 19:23:57 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str_buffer;
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);
int		ft_strchr(t_list *lst);
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstnew(void *lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstlen(t_list *lst);
void	ft_lstdup(t_list *lst, char *str);
void	ft_free(t_list **lst, t_list *clean_node, char *buffer);
#endif
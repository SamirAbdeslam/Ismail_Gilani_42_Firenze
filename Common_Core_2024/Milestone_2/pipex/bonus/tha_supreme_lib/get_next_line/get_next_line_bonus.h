/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:20:09 by igilani           #+#    #+#             */
/*   Updated: 2025/02/25 12:28:23 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "../tha_supreme_lib.h"

char	*get_next_line(int fd);
int		ft_lstchr(t_list *lst);
t_list	*ft_lstnew(void *lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstlen(t_list *lst);
void	ft_lstdup(t_list *lst, char *str);
void	ft_lstfree(t_list **lst, t_list *clean_node, char *buffer);
#endif
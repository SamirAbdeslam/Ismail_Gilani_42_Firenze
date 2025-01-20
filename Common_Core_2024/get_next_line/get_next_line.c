/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:20:11 by igilani           #+#    #+#             */
/*   Updated: 2025/01/21 00:51:32 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	final_line(t_list **lst)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1,	sizeof(char));
	clean_node = ft_calloc(1,sizeof(t_list));
	last_node = ft_lstlast(*lst);
	i = 0;
	k = 0;
	
	while (last_node->str_buffer[i] != '\0' && last_node->str_buffer[i] != '\n')
		++i;
	while (last_node->str_buffer[i] != '\0' && last_node->str_buffer[++i])
		buffer[k++] = last_node->str_buffer[i];
	buffer[k] = '\0';
	clean_node->str_buffer = buffer;
	clean_node->next = NULL;
	ft_free(lst, clean_node, buffer);
}

char	*get_line(t_list *lst)
{
	int		len;
	char	*next_str;

	if (lst == NULL)
		return(NULL);
	len = ft_lstsize(lst);
	next_str = ft_calloc(len + 1,sizeof(char));
	ft_lstdup(lst, next_str);
	return(next_str);
}

void	add_list(t_list **lst)
{
	t_list	*new_node;
	t_list	*last_node;
	
	last_node = NULL;
	if (last_node == NULL)
		new_node = ft_lstnew(*lst);
	else
		last_node = ft_lstlast(*lst);
}

void	create_list(t_list **lst, int fd)
{
	int		bytes_read;
	char	*buffer;

	while (!ft_strchr(*lst, '\n'))
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return;
		}
		buffer[bytes_read] = '\0';
	}
	add_list(lst);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return(NULL);
	next_line = get_line(lst);
	final_line(&lst);
	return (next_line);
}

int main()
{
	int		fd;
	char	*line;
	int		lines;

	lines = 1;
	fd = open("test.txt", O_RDONLY);

	while((line = get_next_line(fd)))
		printf("%d->%s\n", lines++, line);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:20:11 by igilani           #+#    #+#             */
/*   Updated: 2025/01/23 15:48:25 by igilani          ###   ########.fr       */
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

	buffer = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buffer == NULL || clean_node == NULL)
		return ;
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
	ft_lstfree(lst, clean_node, buffer);
}

char	*take_line(t_list *lst)
{
	int		len;
	char	*next_str;

	if (lst == NULL)
		return (NULL);
	len = ft_lstlen(lst);
	next_str = malloc(len + 1);
	if (next_str == NULL)
		return (NULL);
	ft_lstdup(lst, next_str);
	return (next_str);
}

void	add_list(t_list **lst, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(*lst);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->str_buffer = buffer;
	new_node->next = NULL;
}

void	create_list(t_list **lst, int fd)
{
	int		bytes_read;
	char	*buffer;

	while (!ft_lstchr(*lst))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read || bytes_read < 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		add_list(lst, buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	next_line = take_line(lst);
	final_line(&lst);
	return (next_line);
}

// int main()
// {
// 	int		fd;
// 	char		*line;
// 	int		lines;

// 	lines = 1;
// 	fd = open("read_error.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

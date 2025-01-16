/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:49 by igilani           #+#    #+#             */
/*   Updated: 2025/01/16 21:47:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;
	char		*new_pos;
	char		*tmp;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		stash = ft_strjoin(stash, buffer);
		if ((new_pos = ft_strchr(stash, '\n')))
		{
			*new_pos = '\0';
			line = ft_strdup(stash);
			tmp = ft_strdup(new_pos + 1);
			free(stash);
			stash = tmp;
			free(buffer);
			return (line);
		}
		free(buffer);
	}
	if (stash && *stash)
	{
		line = ft_strdup(stash);
		free(stash);
		stash = NULL;
		return (line);
	}
	free(stash);
	stash = NULL;
	return (NULL);
}

// int	main(void)
// {
//     int	fd;

//     fd = open("cacato_nel_puzzo.txt", O_RDONLY);
//     if (fd == -1)
//         return (1);
//     printf("%s\n", get_next_line(fd));
//     printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
//     close(fd);
//     return (0);
// }

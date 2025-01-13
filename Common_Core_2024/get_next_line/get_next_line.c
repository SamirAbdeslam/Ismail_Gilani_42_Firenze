/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:49 by igilani           #+#    #+#             */
/*   Updated: 2025/01/13 19:44:01 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char 	buffer[BUFFER_SIZE];
	static int		buffer_index;
	static ssize_t	bytes_read;
	char			*line;
	int				line_len;

	buffer_index = 0;
	bytes_read = 0;
	line_len = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

	line = malloc(BUFFER_SIZE);
	if (!line)
		return(NULL);
	
	while(!ft_strchr(line, '\n'))
	{
		bytes_read = read(fd,buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
	}

	ft_strlcpy(line,buffer,BUFFER_SIZE);
	
	return(line);
}

int main()
{
	int fd;
	fd = open("cacato_nel_puzzo.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
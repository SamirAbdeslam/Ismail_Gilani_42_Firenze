/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:49 by igilani           #+#    #+#             */
/*   Updated: 2025/01/15 19:03:21 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;
	ssize_t		bytes_read;

	line = NULL;
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if(!buffer)
		return(NULL);

	while((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if(ft_strchr(stash,'\n'))
		{
			stash = ft_strjoin(stash,buffer);
		}
	}
	ft_strlcpy(line, stash, bytes_read);
	return(line);
}
int main(void)
{
	int  fd;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
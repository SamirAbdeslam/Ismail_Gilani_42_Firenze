/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:49 by igilani           #+#    #+#             */
/*   Updated: 2025/01/14 20:29:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char *get_next_line(int fd)
{
	char			buffer[BUFFER_SIZE];
	static char 	*stash;
	char			*line;
	char			*newline;
	//static int		buffer_index;
	static ssize_t	bytes_read;
	int				i;
	i = 0;

	if(fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	buffer = ft_read()
}

int main()
{
	int fd;
	fd = open("cacato_nel_puzzo.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
}
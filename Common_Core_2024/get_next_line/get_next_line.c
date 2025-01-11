/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:05:49 by igilani           #+#    #+#             */
/*   Updated: 2025/01/11 15:07:39 by igilani          ###   ########.fr       */
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
	line = malloc(BUFFER_SIZE);
	if (!line)
		return(NULL);

	bytes_read = read(fd,buffer, BUFFER_SIZE);
}
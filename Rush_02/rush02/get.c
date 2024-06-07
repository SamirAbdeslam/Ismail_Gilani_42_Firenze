/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 23:34:59 by igilani           #+#    #+#             */
/*   Updated: 2024/06/02 23:35:00 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ft.h"

char	*ft_getnb(unsigned long int fd)
{
	unsigned long int	i;
	char				c;
	char				*str;

	str = (char *)malloc(sizeof(char) * 128);
	if (str == NULL)
		exit(1);
	i = 0;
	read(fd, &c, 1);
	while (c == '\n')
		read(fd, &c, 1);
	while (c >= '0' && c <= '9')
	{
		str[i++] = c;
		if (read(fd, &c, 1) <= 0)
			break ;
	}
	str[i] = '\0';
	return (str);
	free(str);
}

char	*ft_getval(unsigned long int fd, char *c)
{
	unsigned long int		i;
	char					*str;

	str = (char *)malloc(sizeof(char) * 128);
	if (str == NULL)
		exit(1);
	i = 0;
	while (*c != '\n')
	{
		str[i++] = *c;
		if (read(fd, c, 1) <= 0)
			break ;
	}
	str[i] = '\0';
	return (str);
	free(str);
}

void	process2(t_list	*tab, int fd)
{
	unsigned long int		i;
	char					c;
	char					*tmp;

	i = 0;
	while (i < 32)
	{
		tab[i].num = ft_atoi(ft_getnb(fd));
		while (read(fd, &c, 1) && c == ' ')
			if (c == ':')
				read(fd, &c, 1);
		while (c == ' ')
			read(fd, &c, 1);
		tmp = ft_getval(fd, &c);
		tab[i].value = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}

t_list	*process(const char *file)
{
	int						fd;
	t_list					*tab;

	tab = (t_list *) malloc(sizeof(t_list) * 128);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error(2);
	if (tab == NULL)
	{
		close(fd);
		exit(1);
	}
	process2(tab, fd);
	close(fd);
	return (tab);
}

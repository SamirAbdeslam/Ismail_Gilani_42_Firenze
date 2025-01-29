/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:20:32 by igilani           #+#    #+#             */
/*   Updated: 2025/01/29 19:10:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	fd[2];
	int i;
	
	if(argc != 2)
		return(0);

	i = pipe(fd);
	if(i == -1)
	{
		printf("%d", i);
		return(0);
	}

	int	id;
	
	id = fork();
	if(id == 0)
	{
		close(fd[0]);
		int x;
		x = argv[1][0];
		write(fd[1], &x, sizeof(int));
		x = argv[1][1];
		write(fd[1], &x, sizeof(int));
		//write(1, &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		int	y;
		y = 0;
		char *s;
		s = NULL;
		y = read(fd[0],s, 2);
		printf("Ricevuto dal figlio: %s", s);
	}
}

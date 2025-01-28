/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:20:32 by igilani           #+#    #+#             */
/*   Updated: 2025/01/28 18:42:51 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
# include <fcntl.h>

void	pipex(int fd1, int fd2 )
{
	
}

int	main(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	errno = EINVAL;
	
	if(argc != 5)
		perror(errno);
		
	fd1 = open(argv[0], O_RDONLY);
	fd2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);

	if(fd1 < 0 || fd2 < 0)
		perror("Errore di apertura");
}

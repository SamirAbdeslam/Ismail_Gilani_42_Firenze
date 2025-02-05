/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:33:53 by igilani           #+#    #+#             */
/*   Updated: 2025/02/05 20:04:49 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
//cambiare con strerror
void	error_handle(int error, int exit_type)
{
	if (error == 0)
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	else if (error == 1)
		ft_putstr_fd("pipe erorr\n", 2);
	else if (error == 2)
		ft_putstr_fd("fork error\n", 2);
	else if (error == 3)
		ft_putstr_fd("command not found\n", 2);
	else if (error == 41)
		ft_putstr_fd("execve child error\n", 2);
	else if (error == 42)
		ft_putstr_fd("execve parent error\n", 2);
	else if (error == 5)
		ft_putstr_fd("input: No such file or directory\n", 2);
	else if (error == 6)
		ft_putstr_fd("output: No such file or directory\n", 2);
	else if (error == 7)
		ft_putstr_fd("path not set\n", 2);
	else
		ft_putstr_fd("generic error\n", 2);
	exit (exit_type);
	return ;
}

void	ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:58:08 by igilani           #+#    #+#             */
/*   Updated: 2025/05/08 16:58:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cd(t_data *data)
{
	char *path;
	char *new_path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("getcwd");
		return ;
	}
	new_path = data->input_array[1];
	printf("Current directory: %s\n", path);
	printf("New directory: %s\n", new_path);
	free(path);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:25:13 by igilani           #+#    #+#             */
/*   Updated: 2025/05/09 17:31:28 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
UNSET HOME funziona sempre
OLDPWD funziona solo se e' settato
ogni cd setta nuovamente OLDPWD e PWD
il comando pwd funziona sempre
*/

static void get_home_path(t_data *data)
{
	while (data->env && ft_strncmp(*data->env, "HOME=", 5) != 0)
		data->env++;
	data->home_path = *data->env + 5;
}

void cd(t_data *data)
{
	char *new_path;

	new_path = data->input_array[1];
	get_home_path(data);
	if (new_path == NULL || (new_path[0] == '~' && new_path[1] == '\0'))
	{
		data->old_path = getcwd(NULL, 4096);
		if (chdir(data->home_path) != 0)
		{
			print_error("bash: cd: no such file or directory\n");
			return ;
		}
		data->current_path = getcwd(NULL, 4096);
	}
	else if (new_path[0] == '~' && new_path[1] != '\0')
	{
		data->old_path = getcwd(NULL, 4096);
		if (chdir(ft_strjoin(data->home_path, new_path + 1)) != 0)
		{
			print_error("bash: cd: no such file or directory\n");
			return ;
		}
		data->current_path = getcwd(NULL, 4096);
	}
	else if (new_path[0] == '-')
	{
		if (chdir(data->old_path) != 0)
		{
			print_error("bash: cd: no such file or directory\n");
			return ;
		}
		ft_printf("%s\n", data->old_path);
		data->current_path = getcwd(NULL, 4096);
	}
	else if (new_path != NULL)
	{
		data->old_path = getcwd(NULL, 4096);
		if (chdir(new_path) != 0)
		{
			print_error("bash: cd: no such file or directory\n");
			return ;
		}
		data->current_path = getcwd(NULL, 4096);
	}
}

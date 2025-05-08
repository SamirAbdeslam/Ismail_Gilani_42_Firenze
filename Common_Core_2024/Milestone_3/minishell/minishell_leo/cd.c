/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:25:13 by igilani           #+#    #+#             */
/*   Updated: 2025/05/08 18:13:53 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_home_path(char **env)
{
	char *home_path;

	while (env && ft_strncmp(*env, "HOME=", 5) != 0)
		env++;
	home_path = *env + 5;
	return (home_path);
}

void cd(t_data *data)
{
	char *new_path;
	char *old_path;
	char *home_path;
	
	old_path = malloc(4096);
	home_path = get_home_path(data->env);
	getcwd(old_path, 4096);
	new_path = data->input_array[1];
	if (new_path == NULL || new_path[0] == '~')
	{
		chdir(home_path);
	}
	else if (new_path[0] == '-')
	{
		chdir(old_path);
	}
	else if (new_path != NULL)
	{
		if (chdir(new_path) != 0)
		{
			print_error("bash: cd: no such file or directory\n");
			return ;
		}
	}
}

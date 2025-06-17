/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:15:50 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/16 18:11:20 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_input(t_data *data, t_cmd *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo(data, cmd, cmd->args), close_if(cmd, data), 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(data, cmd, cmd->args), close_if(cmd, data), 1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd(data, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (env(data, cmd, cmd->args), close_if(cmd, data), 1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset(data, cmd->args), close_if(cmd, data), 1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (export(data, cmd->args), close_if(cmd, data), 1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (exit_shell(data, cmd), close_if(cmd, data), 1);
	return (0);
}

bool	safe_chdir(char *path, int *status, char *s1, char *s2)
{
	if (chdir(path) != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		*status = 1;
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (false);
	}
	return (true);
}

t_env	*new_env_node(char *s)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->e = s;
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **env, t_data *data)
{
	t_env	*first;
	t_env	*curr;
	t_env	*new;
	int		i;

	first = NULL;
	i = 0;
	while (env[i])
	{
		curr = first;
		new = new_env_node(ft_strdup(env[i]));
		if (!first)
			first = new;
		else
		{
			while (curr->next)
				curr = curr->next;
			curr->next = new;
		}
		i++;
	}
	data->current_path = getcwd(NULL, 0);
	data->home_path = getenv("HOME");
	data->old_path = NULL;
	return (first);
}

int	parse_env(char **input_array)
{
	int	i;

	i = 0;
	while (input_array[i])
	{
		if (ft_strcmp(input_array[i], "env") == 0)
			i++;
		else
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:35:46 by igilani           #+#    #+#             */
/*   Updated: 2025/06/16 17:51:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_export(char *var, int *status)
{
	int	i;

	i = 1;
	if (var[0] == '=' || (!ft_isalpha(var[0]) && var[0] != '_'))
	{
		ft_printf_fd(2, EXPORT_IDENT, var);
		*status = 1;
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+' && var[i + 1] == '=')
			return (2);
		else if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_printf_fd(2, EXPORT_IDENT, var);
			*status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_plus(t_data *data, char *args, char *var_name)
{
	char	*replace;

	replace = NULL;
	if (check_env(data, var_name) != NULL)
	{
		replace = ft_strdup(args + ft_strlen(var_name) + 2);
		update_env(data, var_name, replace);
	}
	else
	{
		replace = ft_strjoin(var_name, args + (ft_strlen(var_name) + 1));
		add_env(data, replace);
	}
	free(replace);
}

void	export_add(t_data *data, char *args, char *var_name)
{
	if (check_env(data, var_name) != NULL)
		update_env(data, var_name, (args + (ft_strlen(var_name) + 1)));
	else if (check_env(data, var_name) == NULL)
		add_env(data, args);
	else
		return ;
}

void	export_case(t_data *data, char **args, int *status)
{
	int		i;
	int		parse_result;
	char	*var_name;

	i = 1;
	while (args[i])
	{
		parse_result = parse_export(args[i], status);
		var_name = get_var_name(args[i]);
		if (parse_result == 0 && ft_strncmp(var_name, "_=", 2) != 0)
			export_add(data, args[i], var_name);
		else if (parse_result == 2 && ft_strncmp(var_name, "_=", 2) != 0)
			export_plus(data, args[i], var_name);
		free(var_name);
		i++;
	}
}

void	export(t_data *data, char **args)
{
	t_env	*env;
	int		i;
	int		status;

	i = 0;
	status = 0;
	env = data->env_data;
	if (!args[1])
	{
		while (env)
		{
			i = 0;
			while (env->e[i] != '\0' && env->e[i] != '=')
				i++;
			print_export(env, i);
			env = env->next;
		}
	}
	else
		export_case(data, args, &status);
	data->status = status;
}

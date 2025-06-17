/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:35:46 by igilani           #+#    #+#             */
/*   Updated: 2025/06/13 00:09:08 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strnncmp(char *s1, char *s2, int n1, int n2)
{
	int i;
	
	i = 0;
	if (n1 != n2)
		return (-1);
	while (s1[i] && s2[i] && i < n1 && s1[i] == s2[i])
		i++;
	if (i == n1)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int parse_export(char *var, int *status)
{
	int i;

	i = 1;
	if (var[0] == '=' || (!ft_isalpha(var[0]) && var[0] != '_'))
	{
		ft_printf_fd(2, "minishell: export: %s: not a valid identifier\n", var);
		*status = 1; 
		return (1);
	}
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+' && var[i + 1] == '=')
			return (2);
		else if (!ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_printf_fd(2, "minishell: export: %s: not a valid identifier\n", var);
			*status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

char *get_var_name(char *var)
{
	int i;

	i = 0;
	while (var[i] && (var[i] != '=' && var[i] != '+'))
		i++;
	return (ft_substr(var, 0, i));
}

void export_plus(t_data *data, char *args, char *var_name)
{
	char *replace;
	replace = NULL;
	
	if (check_env(data, var_name) != NULL)
	{
		replace = ft_strjoin(replace, args + ft_strlen(var_name) + 2);
		update_env(data, var_name, replace);
	}
	else
	{
		replace = ft_strjoin(var_name, args + (ft_strlen(var_name) + 1));
		add_env(data, replace);
	}
	free(replace);
}

void export_add(t_data *data, char *args, char *var_name)
{
	if (check_env(data, var_name) != NULL)
		update_env(data, var_name, args + ft_strlen(var_name));
	else if (check_env(data, var_name) == NULL)
		add_env(data, args);
	else
		return ;
}

void export_case(t_data *data, char **args, int *status)
{
	int i;
	int parse_result;
	char *var_name;

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

void print_export(t_env *env, int i)
{
    if (i > 0 && env->e[i] == '=' && ft_strncmp(env->e, "_=", 2) != 0)
    {
        char *var_name = get_var_name(env->e);
        ft_printf("declare -x %s=\"%s\"\n", var_name, &env->e[i + 1]);
        free(var_name);
    }
    else if (ft_strncmp(env->e, "_=", 2) != 0)
        ft_printf("declare -x %s\n", env->e);
}

void export(t_data *data, char **args)
{
	t_env *env;
	int i;
	int	status;

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

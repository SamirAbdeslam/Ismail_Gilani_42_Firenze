/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:43:55 by igilani           #+#    #+#             */
/*   Updated: 2025/05/07 18:41:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_echo_flag(char **input_array)
{
	int i;
	int j;
	
	i = 0;
	j = 1;

	while (input_array[j])
	{
		while (input_array[j][i] != '\0')
		{
			if (input_array[j][0] == '-')
				i++;
			else
				return (j - 1);
			if (input_array[j][i] == 'n')
				i++;
			else
				return (j - 1);
		}
		j++;
	}
	return (j - 1);
}

void echo(t_data *data)
{
	int i;
	int flag;
	flag = check_echo_flag(data->input_array);

	printf("flag: %d\n", flag);
	if (flag > 0)
		i = flag + 1;
	else
		i = 1;
	if (data->input_array[i] == NULL)
	{
		printf("\n");
		return ;
	}
	while (data->input_array[i])
	{
		ft_printf("%s", data->input_array[i]);
		i++;
		if (data->input_array[i])
			ft_printf(" ");
	}
	if (!flag)
		ft_printf("\n");
}
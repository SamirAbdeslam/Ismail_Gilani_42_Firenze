/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:58:08 by igilani           #+#    #+#             */
/*   Updated: 2025/05/09 17:09:32 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cd(t_data *data)
{
	printf("Current directory: %s\n", data->current_path);
	printf("Old directory: %s\n", data->old_path);
}
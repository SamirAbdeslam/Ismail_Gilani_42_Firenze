/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <lmenoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:21:16 by lmenoni           #+#    #+#             */
/*   Updated: 2025/04/07 18:03:46 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    do_echo(t_data *data)
{
    //da implementare eh eh
    ft_printf("%s", data->input_array[1]);
}

int define_input(t_data *data)
{
    if (!ft_strncmp(data->input, "exit", ft_strlen(data->input)))
        return (0);
    if (!ft_strncmp(data->input, "echo", 4))
        return (do_echo(data), 1);
    return (1);
}

int main()
{
    t_data  data;
    
    data = (t_data){0};
    while (1)
    {
        data.input = readline("minishell> ");
        if (!data.input)
            break ;
        data.input_array = ft_split(data.input, ' ');
        if (!define_input(&data))
        {
            free(data.input);
            ft_freemat((void *)data.input_array, ft_matlen(data.input_array));
            break;
        }
        add_history(data.input);
        free(data.input);
        ft_freemat((void *)data.input_array, ft_matlen(data.input_array));
    }
    rl_clear_history();
    return (0);
}
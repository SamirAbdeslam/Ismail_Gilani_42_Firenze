/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:21:16 by lmenoni           #+#    #+#             */
/*   Updated: 2025/05/12 18:43:22 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    define_token_add(t_data *data, char *s, int *idx)
{
    // non so come cazzo farlo dio merda
    if (s[0] == '|')
        return (add_pipe(data, s, idx));
    else if (s[0] == '<' || s[0] == '>')
        return (add_redirect(data, s, idx));
    else if (s[0] == '$')
        return (add_operator(data, s, idx));
    else
        return (add_argument(data, s, idx));
    return ;
}

void    tokenize_input(t_data *data)
{
    int     i;
    bool    in_quotes;
    
    i = 0;
    in_quotes = false;
    while (data->input[i] != '\0')
    {
        skip_spaces(data->input, &i);
        if (data->input[i] == '"')
        {
            in_quotes = !in_quotes;
            i++;
        }
        if (data->input[i] != '\0' && in_quotes)
            add_string(data, &data->input[i], &i);
        skip_spaces(data->input, &i);
        if (data->input[i] != '\0' && data->input[i] != '"' && !in_quotes)
            define_token_add(data, &data->input[i], &i);
    }
}

int define_input(t_data *data)
{
    if (!ft_strncmp(data->input, "echo", 4))
        return (echo(data), 1);
    else if (!ft_strncmp(data->input, "cd", 2))
        return (cd(data), 1);
    else if (!ft_strncmp(data->input, "pwd", 3))
        return (pwd(), 1);
    else if (!ft_strncmp(data->input, "debug cd", 8))
        return (print_cd(data), 1);
    else if (!ft_strncmp(data->input, "env", 9))
        return (env(data), 1);
    else if (!ft_strncmp(data->input, "add env", 7))
        return (add_env(data, data->input + 8), 1);
    else if (!ft_strncmp(data->input, "unset", 5))
        return (unset(data, data->input + 6), 1);
    return (1);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_data  data;
    data = (t_data){0};
    data.env_data = NULL;
    init_env(env, &data);
    data.old_path = getcwd(NULL, 4096);
    data.current_path = getcwd(NULL, 4096);
    while (1)
    {
        data.input = readline(CYAN"minishell"RESET YELLOW">"RESET);
        if (!data.input)
            break ;
        data.token = NULL;
        data.last_token = NULL;
        data.input_array = ft_split(data.input, ' ');
        define_input(&data);
        // tokenize_input(&data);
        // print_tokens(data.token);
        if (!ft_strncmp(data.input, "exit", ft_strlen(data.input)))
        {
            free(data.input);
            break;
        }
        add_history(data.input);
        // ft_printf("Hai scritto: %s\n", data.input);
        free(data.input);
        free_token(data.token);
    }
    rl_clear_history();
    return (0);
}

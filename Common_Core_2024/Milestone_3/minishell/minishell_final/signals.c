/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:11:32 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/13 14:12:20 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	g_last_signal = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

bool	check_last_signal(t_data *data)
{
	if (g_last_signal)
	{
		g_last_signal = 0;
		data->status = 130;
	}
	if (data->input && data->input[0] == '\0')
	{
		free(data->input);
		data->input = NULL;
		rl_on_new_line();
		return (true);
	}
	return (false);
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

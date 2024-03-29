/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:07 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/29 19:06:23 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the signal.
 *
 * @param int sig - The signal to handle.
 * @return void
 */
static void	ft_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handle_quit_signal(int sig)
{
	(void)sig;
	ft_putstr_fd("exit\n", 1);
	g_exit_status = 130;
	exit(g_exit_status);
}

void	ft_init_signals(void)
{
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

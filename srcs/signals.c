/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:07 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 23:34:26 by ugolin-olle      ###   ########.fr       */
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
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/**
 * @brief Handle quit signal.
 *
 * @param int sig - The signal to handle.
 * @return void
 */
void	ft_handle_quit_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: \n", 1);
		ft_putnbr_fd(sig, 1);
		ft_putstr_fd("\n", 1);
	}
}

/**
 * @brief Initialize the signals.
 *
 * @param void
 * @return void
 */
void	ft_init_signals(void)
{
	signal(SIGINT, ft_handle_signal);
	signal(SIGQUIT, ft_handle_quit_signal);
}

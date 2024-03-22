/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:32:59 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 18:30:41 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print an error message, free the lexer structure and exit.
 *
 * @param t_exec *ex - The minishell object.
 * @param char *message - The error message.
 * @param int err_code = Exit error code
 * @return void
 */
void	ft_parser_error(t_exec *ex, char *message, int err_code)
{
	if (message)
	{
		ft_putstr_fd(RED "minishell: " RESET, STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	ex->exit = err_code; 
	ft_free_lexer(ex);
	ft_launch_minishell(ex);
}

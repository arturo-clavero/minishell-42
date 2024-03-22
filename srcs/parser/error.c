/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:32:59 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 15:00:11 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print an error message, free the lexer structure and exit.
 *
 * @param t_exec *ex - The minishell object.
 * @param char *message - The error message.
 * @return void
 */
void	ft_parser_error(t_exec *ex, char *message)
{
	ft_putstr_fd(RED "minishell: " RESET, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	ft_free_lexer(ex);
	ft_launch_minishell(ex);
}

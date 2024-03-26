/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:32:59 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/26 18:16:29 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print an error message, free the lexer structure and exit.
 *
 * @param t_exec *ex - The minishell object.
 * @param int err_code = Exit error code
 * @return void
 */
void	ft_parser_error(t_exec *ex, int err_code)
{
	ex->exit = err_code;
	ft_free_lexer(ex);
	ft_launch_minishell(ex);
}

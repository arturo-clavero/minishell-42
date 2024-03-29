/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:32:59 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/29 09:43:25 by ugolin-olle      ###   ########.fr       */
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
void	ft_parser_clean(t_exec *ex, int err_code)
{
	g_exit_status = err_code;
	ft_free_lexer(ex);
	ft_launch_minishell(ex);
}

/**
 * @brief Print redirection error message and relaunch minishell.
 *
 * @param t_exec *ex - The minishell object.
 * @param int status - The status of the error.
 * @return void
 */
void	ft_parser_error(t_exec *ex, int status)
{
	if (status == 1)
		ft_putstr_fd(ERROR_NEWLINE, STDERR_FILENO);
	else if (status == 2)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
	else if (status == 404)
		ft_putstr_fd(ERROR_NO_CLOSE_QUOTE, STDERR_FILENO);
	ft_parser_clean(ex, 2);
}

/**
 * @brief Print syntax error and relaunch minishell.
 *
 * @param t_exec *ex - The minishell object.
 * @param int token - The token of the error.
 * @param int status - The status of the error.
 * @return void
 */
void	ft_syntax_error(t_exec *ex, int token, int status)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token == PIPE)
		ft_putstr_fd("|'\n", STDERR_FILENO);
	else if (token == APPEND)
		ft_putstr_fd(">>'\n", STDERR_FILENO);
	else if (token == OUTFILE)
		ft_putstr_fd(">'\n", STDERR_FILENO);
	else if (token == INFILE)
		ft_putstr_fd("<'\n", STDERR_FILENO);
	else if (token == HEREDOC)
		ft_putstr_fd("<<'\n", STDERR_FILENO);
	else if (token == 7)
		ft_putstr_fd("<<<'\n", STDERR_FILENO);
	ft_parser_clean(ex, status);
}

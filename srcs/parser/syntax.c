/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:16:32 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/26 13:14:18 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check the syntax of the lexer.
 *
 * @param t_lexer *lexer - The lexer object.
 * @return void
 */
void	ft_check_syntax(t_exec *ex)
{
	t_lexer *lexer;

	lexer = ex->lexer;
	if (lexer->token == PIPE)
		ft_parser_error(ex, ERROR_SYNTAX, "|", 2);
}

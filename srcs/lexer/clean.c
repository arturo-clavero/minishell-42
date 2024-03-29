/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:31:44 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/29 11:52:52 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free the lexer.
 *
 * @param t_exec *ex - The execution structure.
 * @return void
 */
void	ft_free_lexer(t_exec *ex)
{
	t_lexer	*tmp;
	t_lexer	*lexer;

	lexer = ex->lexer;
	if (!lexer)
		return ;
	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->str)
			free_data((void **)&lexer->str, 0);
		free_data((void **)&lexer, 0);
		lexer = tmp;
	}
	ex->lexer = NULL;
}

/**
 * @brief Lexer error.
 *
 * @param t_exec *ex - The execution structure.
 * @param char *str - The error message.
 * @return void
 */
void	ft_lexer_error(t_exec *ex, char *str)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_free_lexer(ex);
	ft_launch_minishell(ex);
}

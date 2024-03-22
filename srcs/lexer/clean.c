/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:31:44 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 15:00:34 by artclave         ###   ########.fr       */
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
			free(lexer->str);
		free(lexer);
		lexer = tmp;
	}
	ex->lexer = NULL;
}

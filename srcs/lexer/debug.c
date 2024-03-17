/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:45:52 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/18 00:54:07 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print the lexer.
 *
 * @param t_lexer *lexer The lexer to print.
 */
void	ft_debug_lexer(t_lexer *lexer)
{
	while (lexer)
	{
		printf("\nLexer: \n");
		printf("str: %s\n", lexer->str);
		printf("token: %d\n", lexer->token);
		printf("\n");
		lexer = lexer->next;
	}
	ft_free_lexer(lexer);
}

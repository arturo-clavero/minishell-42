/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:45:52 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/20 22:50:40 by ugolin-olle      ###   ########.fr       */
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
	printf("\n=====================================\n\n");
	printf("\nLexer:\n\n");
	while (lexer)
	{
		printf("lexer->str: %s\n", lexer->str);
		printf("lexer->token: %d\n\n", lexer->token);
		lexer = lexer->next;
	}
}

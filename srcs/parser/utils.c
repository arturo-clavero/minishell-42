/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:40:16 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/20 20:02:06 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the string has close quotes.
 *
 * @param char *str The string to check.
 * @param int i The index of the string.
 * @param char c The quote to check.
 * @return int 0 if the string has close quotes, 1 otherwise.
 */
int	ft_close_quotes(char *str, int i, char c)
{
	if (str == NULL || (c != '"' && c != '\''))
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Count token from lexer.
 *
 * @param t_lexer *lexer - The lexer structure.
 * @return int - The number of token.
 */
int	ft_count_token(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->token == WORD || lexer->token == UNINITIALIZED
			|| lexer->token == PIPE)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

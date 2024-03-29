/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:32:30 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/27 18:59:03 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the character is a operator.
 *
 * @param int c The character to check.
 * @return int 1 if the character is a operator, 0 otherwise.
 */
t_token_type	ft_check_string_token(int c)
{
	static const char			operators[] = "|<>";
	static const t_token_type	operator_types[] = {PIPE, INFILE, OUTFILE};
	unsigned long				i;

	if (c == 0)
		return (UNINITIALIZED);
	i = 0;
	while (i < sizeof(operators))
	{
		if (operators[i] == c)
			return (operator_types[i]);
		i++;
	}
	return (UNINITIALIZED);
}

/**
 * @brief Get the word from the command line and complete the lexer.
 *
 * @param char *str The command line.
 * @param int i The index of the command line.
 * @param t_lexer *lexer The lexer to complete.
 * @return void
 */
int	ft_get_word(char *str, int i, t_lexer *lexer)
{
	int	n;

	n = 0;
	while (str[i + n] && ft_check_string_token(str[i + n]) <= 1)
	{
		n += ft_handle_quote(str, i + n, 34);
		n += ft_handle_quote(str, i + n, 39);
		if (ft_is_space(str[i + n]))
			break ;
		else
			n++;
	}
	if (!ft_add_lexer(ft_substr(str, i, n), WORD, lexer))
		return (-1);
	return (n);
}

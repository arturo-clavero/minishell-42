/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:32:30 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/17 00:50:43 by ugolin-olle      ###   ########.fr       */
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
	static const char			operators[] = "|<>>";
	static const t_token_type	operator_types[] = {PIPE, INFILE, OUTFILE,
			APPEND, HEREDOC};
	unsigned long				i;

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
		n += ft_handle_quote(str, i + n, '\"');
		n += ft_handle_quote(str, i + n, '\'');
		if (ft_is_space(str[i + n]))
			break ;
		else
			n++;
	}
	if (!ft_add_lexer(ft_substr(str, i, n), WORD, lexer))
		return (-1);
	return (n);
}

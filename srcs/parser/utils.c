/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:40:16 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/21 00:30:18 by ugolin-olle      ###   ########.fr       */
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
 * @brief Get the file name after or before the redirection.
 *
 * @param t_lexer *lexer - The lexer structure.
 * @return char * - The file name.
 */
char	*ft_get_file_name(t_lexer *lexer)
{
	char	*file_name;

	file_name = NULL;
	if (lexer->next && lexer->next->str)
		file_name = lexer->next->str;
	return (file_name);
}

/**
 * @brief Get heredoc buffer.
 *
 * @param t_lexer *lexer - The lexer structure.
 * @return char * - The heredoc buffer.
 */
char	*ft_get_heredoc_buff(t_lexer *lexer)
{
	char	*heredoc_buff;

	heredoc_buff = NULL;
	if (lexer->next && lexer->next->str)
		heredoc_buff = lexer->next->str;
	return (heredoc_buff);
}

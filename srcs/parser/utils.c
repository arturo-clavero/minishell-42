/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:40:16 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/23 00:08:54 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

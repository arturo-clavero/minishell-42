/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:39:09 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/20 20:05:59 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the file name after or before the redirection.
 *
 * @param t_lexer *lexer - The lexer structure.
 * @param char *str - The string to get.
 * @return char * - The file name.
 */
char	*ft_get_file_name(t_lexer *lexer, char *str)
{
	char	*file_name;

	file_name = NULL;
	if (lexer->next && lexer->next->str)
		file_name = lexer->next->str;
	else if (str)
		file_name = str;
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

/**
 * @brief The main function for the paser.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
void	ft_parser(t_exec *ex)
{
	t_lexer	*lexer;
	t_redir	*redir;
	t_cmd	*cmd;

	lexer = ex->lexer;
	cmd = ex->cmd;
	redir = cmd->redir;
	while (lexer)
	{
		if (lexer->str)
		{
			if (!ft_close_quotes(lexer->str, 0, '\'')
				&& !ft_close_quotes(lexer->str, 0, '"'))
				ft_parser_error(ex, ERROR_NO_CLOSE_QUOTE);
			ft_add_cmd(&cmd, &lexer->str, redir, ft_count_token(lexer));
		}
		// if (lexer->token > 1)
		// 	if (lexer->token == OUTFILE)
		// 		ft_add_redir(redir, ft_get_file_name(lexer, NULL), NULL,
		// 			OUTFILE);
		lexer = lexer->next;
	}
	ft_debug_parser(ex->cmd);
}

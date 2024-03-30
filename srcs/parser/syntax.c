/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:16:32 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/30 15:03:22 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check redirection syntax.
 *
 * @param t_lexer *lexer - The lexer object.
 * @param t_exec *ex - The minishell object.
 * @return void
 */
static void	ft_check_redirection_syntax(t_lexer *lexer, t_exec *ex)
{
	int	count;

	if (lexer->token == INFILE || lexer->token == HEREDOC)
	{
		count = 1;
		while (lexer->next && lexer->next->token == INFILE)
		{
			count++;
			lexer = lexer->next;
		}
		if (count >= 6)
			ft_syntax_error(ex, 7, STDERR_FILENO);
		if (count >= 5)
			ft_syntax_error(ex, HEREDOC, STDERR_FILENO);
		if (count >= 4)
			ft_syntax_error(ex, lexer->token, STDERR_FILENO);
		if (count >= 3)
			ft_syntax_error(ex, INFILE, STDERR_FILENO);
	}
}

/**
 * @brief Count number of token in a row except WORD and UNINITIALIZED.
 *
 * @param t_lexer *lexer - The lexer object.
 * @return int - The number of token.
 */
static int	ft_count_tokens(t_lexer *lexer)
{
	int	count;
	int	consecutive_count;

	count = 0;
	consecutive_count = 0;
	while (lexer)
	{
		if (lexer->token != WORD && lexer->token != UNINITIALIZED
			&& lexer->token != PIPE && lexer->token != INFILE
			&& lexer->token != HEREDOC)
		{
			consecutive_count++;
			if (consecutive_count == 3)
			{
				count++;
				consecutive_count = 0;
			}
		}
		else
			consecutive_count = 0;
		lexer = lexer->next;
	}
	return (count);
}

/**
 * @brief Check if there are double pipes.
 *
 * @param t_lexer *lexer - The lexer object.
 * @param t_exec *ex - The minishell object.
 * @return void
 */
static void	ft_double_pipes(t_lexer *lexer, t_exec *ex)
{
	while (lexer)
	{
		if (lexer->token == PIPE)
		{
			if (lexer->next && lexer->next->token == PIPE)
				ft_syntax_error(ex, lexer->next->token, STDERR_FILENO);
			else if (lexer->prev && (lexer->prev->token == APPEND
					|| lexer->prev->token == OUTFILE
					|| lexer->prev->token == INFILE
					|| lexer->prev->token == HEREDOC))
				ft_syntax_error(ex, lexer->token, STDERR_FILENO);
			else if (lexer->prev && lexer->prev->token == OUTFILE)
				ft_syntax_error(ex, PIPE, STDERR_FILENO);
		}
		lexer = lexer->next;
	}
}

/**
 * @brief Check if there is a file name after a redirection.
 *
 * @param t_lexer *lexer - The lexer object.
 * @param t_exec *ex - The minishell object.
 * @return void
 */
static void	ft_check_redirection(t_lexer *lexer, t_exec *ex)
{
	while (lexer)
	{
		if (lexer->token == APPEND || lexer->token == OUTFILE
			|| lexer->token == INFILE || lexer->token == HEREDOC)
		{
			if (!lexer->next)
				ft_parser_error(ex, 1);
			else if ((lexer->token == APPEND || lexer->token == OUTFILE)
				&& lexer->next->token == INFILE)
				ft_syntax_error(ex, INFILE, STDERR_FILENO);
		}
		lexer = lexer->next;
	}
}

/**
 * @brief Check the syntax of the lexer.
 *
 * @param t_lexer *lexer - The lexer object.
 * @return void
 */
void	ft_check_syntax(t_exec *ex)
{
	t_lexer	*lexer;

	lexer = ex->lexer;
	if (lexer->token == PIPE)
		ft_parser_error(ex, 2);
	while (lexer)
	{
		ft_check_redirection_syntax(lexer, ex);
		ft_double_pipes(lexer, ex);
		ft_check_redirection(lexer, ex);
		if (ft_count_tokens(lexer) == 1)
			ft_syntax_error(ex, lexer->next->next->token, STDERR_FILENO);
		lexer = lexer->next;
	}
}

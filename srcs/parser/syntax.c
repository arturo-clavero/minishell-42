/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 12:16:32 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/26 14:27:34golin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count number of tokens in the lexer.
 *
 * @param t_lexer *lexer - The lexer object.
 * @return int - The number of tokens.
 */
static int	ft_count_tokens(t_lexer *lexer)
{
	int	count;

	count = 0;
	while (lexer)
	{
		if (lexer->token != WORD && lexer->token != UNINITIALIZED)
			count++;
		lexer = lexer->next;
	}
	return (count);
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
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		ft_parser_error(ex, 2);
	}
	while (lexer)
	{
		if (lexer->token == PIPE && lexer->next->token == PIPE)
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			ft_parser_error(ex, 2);
		}
		if (ft_count_tokens(lexer) > 2)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			ft_parser_error(ex, 2);
		}
		lexer = lexer->next;
	}
}

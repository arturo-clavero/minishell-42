/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:24:45 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/28 03:32:59 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the character is a quote.
 *
 * @param char *str - The character to check.
 * @param int i - The index of the character in the string.
 * @param char quote - The quote to check.
 * @return int - 1 if the character is a quote, 0 otherwise.
 */
int	ft_handle_quote(char *str, int i, char quote)
{
	int	n;

	n = 0;
	if (str[i + n] == quote)
	{
		n++;
		while (str[i + n] && str[i + n] != quote)
			n++;
	}
	return (n);
}

/**
 * @brief Read the token from the string and complete the lexer.
 *
 * @param t_lexer *lexer - The lexer to complete.
 * @param char *str - The string to read.
 * @param int i - The index of the string to read.
 * @return int -
 */
int	ft_handle_token(t_lexer *lexer, char *str, int i)
{
	t_token_type	type;

	type = ft_check_string_token(str[i]);
	if (type)
	{
		if (!ft_add_lexer(NULL, type, lexer))
			return (0);
		return (1);
	}
	return (0);
}

void	check_empty_str(t_exec *exec)
{
	int	i;

	i = -1;
	while (exec->args[++i])
	{
		if (exec->args[i] == 0)
			ft_lexer_error(exec, NULL);
		if (exec->args[i] != ' ')
			break ;
	}
	if (i == (int)ft_strlen(exec->args))
		ft_parser_error(exec, 2);
}

void	check_unclosed_quotes(t_exec *exec)
{
	char	*str;
	int		i;
	int		double_q;
	int		single_q;

	double_q = FALSE;
	single_q = FALSE;
	str = exec->args;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' && single_q == FALSE)
			double_q ^= 1;
		if (str[i] == '\'' && double_q == FALSE)
			single_q ^= 1;
	}
	if (single_q == TRUE || double_q == TRUE)
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		ft_parser_error(exec, 2);
	}
}
/*
void	check_syntax(t_lexer *lex, t_exec *exec);

void	update_token(int new_type, t_lexer *update, t_exec *ex)
{
	t_lexer	*lex;
	t_lexer	*delete;

	lex = ex->lexer;
	while (lex != update)
		lex = lex->next;
	lex->token = new_type;
	delete = lex->next;
	if (delete)
	{
		lex->next = delete->next;
		if (delete->str)
			free_data(NULL, (void *)delete->str, 0);
		free_data(NULL, (void *)delete, 0);
		if (lex->next)
			check_syntax(lex->next, ex);
	}
}

void	syntax_error(t_lexer *lex, t_exec *ex)
{
	(void)lex;
	printf("SYNTAX ERROR\n");
	ft_parser_error(ex, 2);
}

void	check_syntax(t_lexer *lex, t_exec *ex)
{
	while (lex)
	{
		if (lex->token != WORD)
		{
			if (lex == ex->lexer && lex->token == PIPE)
				syntax_error(lex, ex);
			if (!lex->next)
				syntax_error(lex, ex);
			if (lex->next->token != WORD)
			{
				if (lex->token == OUTFILE && lex->next->token == OUTFILE)
					update_token(APPEND, lex, ex);
				if (lex->token == INFILE && lex->next->token == INFILE)
					update_token(HEREDOC, lex, ex);
				else if (!(lex->token == PIPE && lex->next->token != PIPE))
					syntax_error(lex, ex);
			}
		}
		lex = lex->next;
	}
}
*/

/**
 * @brief The main function of the lexer.
 *
 * @param t_exec *exec - The structure of the minishell.
 * @return void
 */
void	ft_lexer(t_exec *exec)
{
	int	i;
	int	j;

	check_empty_str(exec);
	check_unclosed_quotes(exec);
	i = 0;
	while (exec->args[i])
	{
		j = 0;
		skip_whitespace(exec->args, &i);
		if (exec->args[i] && ft_check_string_token(exec->args[i]))
			j = ft_handle_token(exec->lexer, exec->args, i);
		else if (exec->args[i])
			j = ft_get_word(exec->args, i, exec->lexer);
		if (j < 0)
			return ;
		i += j;
	}
	//check_syntax(exec->lexer, exec);
	//ft_debug_lexer(exec->lexer);
}

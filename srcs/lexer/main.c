/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:24:45 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/23 12:17:31 by artclave         ###   ########.fr       */
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
		ft_parser_error(exec, "Unclosed quotes", 404);
}

void	check_empty_str(t_exec *exec)
{
	int	i;

	i = -1;
	while (exec->args[++i])
	{
		if (exec->args[i] != 0 || exec->args[i] != ' ')
			break ;
	}
	if (i == (int)ft_strlen(exec->args))
		ft_parser_error(exec, NULL, 0);
}

void	delete_lexer_node(t_lexer *delete, t_lexer **list)
{
	printf("check\n");
	if (*list == delete)
	{
		printf("delete first\n");
		(*list) = (*list)->next;
		//printf("{%d}{%d}\n", (*list)->token, (*list)->next->token);
		//(*list)->token = (*list)->next->token;
		//printf("{%d}{%d}\n", (*list)->token, (*list)->next->token);
		(*list) = (*list);
		printf("end first\n");
	}
	else
	{
		while (*list)
		{
			if ((*list)->next == delete)
			{
				(*list)->next = (*list)->next->next;
				//(*list)->token = (*list)->next->token;
			}
			(*list) = (*list)->next;
		}
	}
	free(delete);
	printf("end free \n");
}

void	lexer_redirection(t_lexer *lex, t_exec *ex)
{
	int	redir;

	redir = FALSE;
	while (lex)
	{
		if (lex->token != PIPE && lex->token != WORD)
			redir = lex->token;
		else if (lex->token == WORD && redir != FALSE)
		{
			lex->token = redir;
			redir = FALSE;
		}
		lex = lex->next;
	}
	lex = ex->lexer;
	while (lex)
	{
		if (lex->token != PIPE && lex->token != WORD && lex->str == NULL)
			delete_lexer_node(lex, &ex->lexer);
		lex = lex->next;
	}
}

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
		if (ft_check_string_token(exec->args[i]))
			j = ft_handle_token(exec->lexer, exec->args, i);
		else
			j = ft_get_word(exec->args, i, exec->lexer);
		if (j < 0)
			return ;
		i += j;
	}
	//lexer_redirection(exec->lexer, exec);
}

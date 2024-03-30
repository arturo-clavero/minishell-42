/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:24:59 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 16:06:40 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief trim found quote if not inside other quote
 * @param str - pointer to string with quote
 * @param i - pointer to index qhere quote was found
 * @param found - pointer to int indicating type of quote found,
 * and if we are in/ or outside this quote type (single or double)
 * @param other - int ndicating type of quote not found,
 * and if we are in/ or outside this quote type (single or double)
 */
void	trim_quote(char **str, int *i, int *quote)
{
	*quote ^= 1;
	delete_char_from_str(*i, str);
	*i = *i - 1;
}

static void	ft_quote_error(int dq, int sq, t_cmd *cmd, t_exec *ex)
{
	if (dq == OPEN || sq == OPEN)
	{
		clean_t_cmd(cmd, ex);
		ft_parser_error(ex, 404);
	}
}

/**
 * @brief Evaluates if quote found should be deleted or not
 *
 * @param str - string where quote was found
 * @return same string with quotes trimmed or not
 */
static t_cmd	*handle_quotes(t_cmd *cmd, t_exec *ex)
{
	int	i;
	int	j;
	int	dq;
	int	sq;

	dq = CLOSED;
	sq = CLOSED;
	i = -1;
	while (cmd->array[++i])
	{
		j = -1;
		while (cmd->array[i][++j])
		{
			if ((cmd->array[i][j] == '\'' && dq == OPEN)
					|| (cmd->array[i][j] == '"' && sq == OPEN))
				continue ;
			else if (cmd->array[i][j] == '\'')
				trim_quote(&(cmd->array[i]), &j, &sq);
			else if (cmd->array[i][j] == '"')
				trim_quote(&(cmd->array[i]), &j, &dq);
		}
	}
	ft_quote_error(dq, sq, cmd, ex);
	return (cmd);
}

void	redir_quotes(t_redir *rd)
{
	int	i;
	int	dq;
	int	sq;

	if (!(rd->file_name) || (rd->file_name)[0] == 0)
		return ;
	dq = CLOSED;
	sq = CLOSED;
	i = -1;
	while (rd->file_name[++i])
	{
		if ((rd->file_name[i] == '\'' && dq == OPEN)
			|| (rd->file_name[i] == '"'
				&& sq == OPEN))
			continue ;
		else if (rd->file_name[i] == '\'')
			trim_quote(&(rd->file_name), &i, &sq);
		else if (rd->file_name[i] == '"')
			trim_quote(&(rd->file_name), &i, &dq);
	}
}

/**
 * @brief if quote is found it sends the string to be evaluated for trimming
 * @param cmd - cmd list
 * @param ex - main execution structure
 */
void	quotes(t_cmd *cmd, t_exec *ex)
{
	int	i;
	int	j;
	int	next;

	while (cmd)
	{
		i = -1;
		next = FALSE;
		while (!next && cmd->array && cmd->array[++i])
		{
			j = -1;
			while (!next && cmd->array[i][++j])
			{
				if (cmd->array[i][j] == '"' || cmd->array[i][j] == '\'')
				{
					cmd = handle_quotes(cmd, ex);
					next = TRUE;
				}
			}
		}
		if (cmd->redir && cmd->redir->file_name)
			redir_quotes(cmd->redir);
		cmd = cmd->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:24:59 by artclave          #+#    #+#             */
/*   Updated: 2024/03/22 23:31:24 by artclave         ###   ########.fr       */
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
static void	handle_quote(char **str, int *i, int *found, int other)
{
	(*found) ^= 1;
	if (other == FALSE || *found == FALSE)
	{
		delete_char_from_str(*i, str);
		*i = *i - 1;
	}
}

/**
 * @brief evaluates if quote found should be deleted or not 
 * @param str - string where quote was found
 * @return same string with quotes trimmed or not 
 */
static t_cmd	*delete_quotes(t_cmd *cmd)
{
	int	i;
	int	j;
	int	double_q;
	int	single_q;

	double_q = FALSE;
	single_q = FALSE;
	i = -1;
	while (cmd->array[++i])
	{
		j = -1;
		while (cmd->array[i][++j])
		{
			if (cmd->array[i][j] == '\'')
				handle_quote(&cmd->array[i], &j, &single_q, double_q);
			else if (cmd->array[i][j] == '"')
				handle_quote(&cmd->array[i], &j, &double_q, single_q);
		}
	}
	return (cmd);
}

/**
 * @brief if quote is found it sends the string to be evaluated for trimming
 * @param cmd - cmd list
 * @param ex - main execution structure
 */
void	quotes(t_cmd *cmd)
{
	int		i;
	int		j;
	int		next;

	while (cmd)
	{
		i = -1;
		next = FALSE;
		while (!next && cmd->array[++i])
		{
			j = -1;
			while (!next && cmd->array[i][++j])
			{
				if (cmd->array[i][j] == '"' || cmd->array[i][j] == '\'')
				{
					cmd = delete_quotes(cmd);
					next = TRUE;
				}
			}
		}
		cmd = cmd->next;
	}
}

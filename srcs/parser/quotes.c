/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 15:24:59 by artclave          #+#    #+#             */
/*   Updated: 2024/03/22 18:32:24 by artclave         ###   ########.fr       */
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
	if (other == FALSE)
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
static char	*delete_quotes(char *str)
{
	int	i;
	int	double_q;
	int	single_q;

	double_q = FALSE;
	single_q = FALSE;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			handle_quote(&str, &i, &single_q, double_q);
			continue ;
		}
		if (str[i] == '"')
		{
			handle_quote(&str, &i, &double_q, single_q);
			continue ;
		}
	}
	if (double_q == TRUE || single_q == TRUE)
		return (NULL);
	return (str);
}

/**
 * @brief if quote is found it sends the string to be evaluated for trimming
 * @param cmd - cmd list
 * @param ex - main execution structure
 */
void	quotes(t_exec *ex)
{
	int		i;
	char	*str;
	int		flag;

	str = ex->args;
	if (!str)
		return ;
	i = -1;
	flag = FALSE;
	while (str[++i])
	{
		if(str[i] != 0 && str[i] != ' ')
			flag = TRUE;
		if (str[i] == '"' || str[i] == '\'')
		{
			str = delete_quotes(str);
			if (str == NULL)
				ft_parser_error(ex, "Unclosed quotes\n", 404);
			return ;
		}
	}
	if (flag == FALSE)
		ft_parser_error(ex, NULL, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:11:47 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 23:35:27 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Skip the spaces in the string.
 *
 * @param char *str - The string to handle
 * @param int i - The index of the string
 * @return int
 */
int	ft_skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while ((str[i + j] == ' ' || (str[i + j] > 8 && str[i + j] < 14)))
		j++;
	return (j);
}

/**
 * @brief Handle the quotes.
 *
 * @param char *str - The string to handle
 * @param int i - The index of the string
 * @param char quote - The quote type
 */
int	ft_quotes(char *str, int i, char quote)
{
	int	j;

	j = 0;
	if (str[i + j] == quote)
	{
		j++;
		while (str[i + j] != quote && str[i + j] != '\0')
			j++;
		j++;
	}
	return (j);
}

/**
 * @brief Check for token in the string.
 *
 * int c - The character to check
 */
int	ft_tokens(int c)
{
	unsigned long	i;

	static char tokens[][2] = {
		{'|', PIPE}, {'<', INFILE}, {'>', OUTFILE},
		// {'>>', APPEND},
	};
	i = 0;
	while (i < sizeof(tokens) / sizeof(tokens[0]))
	{
		if (c == tokens[i][0])
			return (tokens[i][1]);
		i++;
	}
	return (-1);
}

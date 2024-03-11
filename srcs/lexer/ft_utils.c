/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:11:47 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 14:51:44 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	j = i;
	while (str[++j])
	{
		if (str[j] == quote)
			return (j);
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
		{'|', PIPE},
		{'<', INFILE},
		{'>', OUTFILE},
		{'>>', APPEND},
	};
	i = 0;
	while (i < sizeof(tokens) / sizeof(tokens[0]))
	{
		if (c == tokens[i][0])
			return (tokens[i][1]);
		i++;
	}
	return (0);
}

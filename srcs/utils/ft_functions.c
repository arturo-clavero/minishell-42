/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:06:09 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/02/28 11:07:52 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a character is a digit
 *
 * @param char c - the character to check
 * @return int - TRUE if the character is a digit, FALSE otherwise
*/
int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Check if a character is a letter
 *
 * @param char c - the character to check
 * @return int - TRUE if the character is a letter, FALSE otherwise
*/
int	is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Check if a character is a letter or a digit
 *
 * @param char c - the character to check
 * @return int - TRUE if the character is a letter or a digit, FALSE otherwise
*/
void	skip_whitespace(char *str, int *i)
{
	if (!str)
		return ;
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
}

/**
 * @brief Check if a string is numerical
 *
 * @param char *str - the string to check
 * @return int - TRUE if the string is numerical, FALSE otherwise
*/
int	str_is_numerical(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_digit(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

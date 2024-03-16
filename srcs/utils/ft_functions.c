/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:06:09 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/17 00:18:27 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a character is a letter or a digit
 *
 * @param char c - The character to check
 * @param int - The index of the character in the string
 * @return int - TRUE if the character is a letter or a digit, FALSE otherwise
 */
void	skip_whitespace(char *str, int *i)
{
	if (!str)
		return ;
	while (str[*i] == ' ' || str[*i] == '\t' || (str[*i] > 8 && str[*i] < 14))
		(*i)++;
}

/**
 * @brief Join two strings with a separator
 *
 * @param char const *s1 - The first string
 * @param char const *s2 - The second string
 * @param char sep - The separator
 * @return char* - The result of the join
 */
char	*ft_strjoin_with_sep(char const *s1, char const *s2, char sep)
{
	char	*result;
	int		len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s2[i] != ' ' && s2[i] != '\0')
		i++;
	len = ft_strlen(s1) + i + 1;
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	result[i] = sep;
	while (s2[j] != ' ' && s2[j] != '\0')
		result[++i] = s2[j++];
	result[++i] = '\0';
	return (result);
}

/**
 * @brief Check if a string is a number
 *
 * @param char *str - The string to check
 * @return int - TRUE if the string is a number, FALSE otherwise
 */
int	ft_isnum(char str)
{
	if (str >= '0' && str <= '9')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Check if a string is numerical
 *
 * @param char *str - The string to check
 * @return int - TRUE if the string is numerical, FALSE otherwise
 */
int	ft_is_numericable(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_isdigit(str[i]) == FALSE)
			return (FALSE);
	return (TRUE);
}

/**
 * @brief Check if the string a space.
 *
 * @param int c - The character to check.
 * @return int - TRUE if the string is a space, FALSE otherwise.
 */
int	ft_is_space(int c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

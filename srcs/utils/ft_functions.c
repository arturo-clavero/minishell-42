/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:06:09 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/07 21:46:24 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_isdigit(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
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

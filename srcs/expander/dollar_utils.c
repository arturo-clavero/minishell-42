/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:40:31 by artclave          #+#    #+#             */
/*   Updated: 2024/03/28 18:45:22 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	manipulates string based on curly brackets syntax
 *
 * @param char **str - pointer to string being manipulated
 * @param int j - index of first char right after '$'
 * @return int - (-1) for curly bracket syntax error, (0) for no error
 */
int	check_curly_brackets(char **str, int j)
{
	int	i;

	i = j;
	if ((*str)[i] != '{')
		return (0);
	while ((*str)[i] && (*str)[i] != '}')
		i++;
	if ((*str)[i] == '\0')
		return (-1);
	if ((*str)[j + 1] == '?')
		return (trim_question_mark(str, j));
	i = j;
	while ((*str)[++i] && (*str)[i] != '}')
	{
		if (!ft_isdigit((*str)[i]) && !ft_isalpha((*str)[i])
			&& (*str)[i] != '_')
			return (-1);
	}
	trim_curly_brackets_only(str, j);
	return (0);
}

/**
 * @brief modifies string for correct extraction of expanded value
 * @param input string to modify
 * @return modified string
 */
char	*modify_str_for_expansion(char *input)
{
	char	*str;
	int		i;

	str = ft_strjoin(input, "=\0");
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			delete_char_from_str(i, &str);
			i--;
		}
		if (str[i] == ' ' || str[i] == '\t')
		{
			while (str[i] != '=')
				delete_char_from_str(i, &str);
			break ;
		}
	}
	return (str);
}

/**
 * @brief check if there's a dollar sign with no value to expand
 * @param str string to evaluate
 * @param i index of found dollar sign
 * @param double_quotes = TRUE if inside double quotes, otherwise = FALSE
 * @return 
 */
int	only_dollar_sign(char *str, int i, int double_quotes)
{
	i++;
	if (!str[i] || str[i] == ' ' || str[i] == 0 || str[i] == '\t'
		|| (str[i] == '"' && double_quotes == TRUE))
		return (TRUE);
	return (FALSE);
}

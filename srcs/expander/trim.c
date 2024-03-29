/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:57:26 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 01:00:08 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief if no expansion value is found $VARIABLE is trimmed
 * 
 * @param char **str - pointer to str being trimmed
 * @return int - 0 
 */
int	trim_dollar_substr(char *str, char **original)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while (str[i] != '$')
		i++;
	j = i;
	while (str[j] && str[j] != ' ' && str[j] != '\t')
		j++;
	str[i] = '\0';
	result = ft_strjoin(str, &str[j]);
	*original = result;
	free_data((void **)original, 0);
	return (0);
}

/**
 * @brief trims garbage values within ${} when '?' is the first char
 * found within ${}
 * 
 * @param char **str - pointer to string to be modified
 * @param int j - index of char right after first '?'
 * @return int (0)
 */
int	trim_question_mark(char **str, int j)
{
	char	*result;
	int		i;

	i = j;
	while ((*str)[i] && (*str)[i] != '}')
		i++;
	(*str)[j] = '\0';
	result = ft_join_3_strings(*str, "?", &(*str)[i + 1]);
	free_data((void **)str, 0);
	*str = result;
	return (0);
}

/**
 * @brief trims curly brackets found after '$'
 * 
 * @param char **str - pointer to str being modified
 * @param int j - index of closing curly bracket '}'
 * @return int (0)
 */
int	trim_curly_brackets_only(char **str, int j)
{
	char	*result;
	int		i;

	i = j;
	while ((*str)[i] && (*str)[i] != '}')
		i++;
	(*str)[i] = '\0';
	(*str)[j] = '\0';
	result = ft_join_3_strings(*str, &(*str)[j + 1], &(*str)[i + 1]);
	free_data((void **)str, 0);
	*str = result;
	return (0);
}

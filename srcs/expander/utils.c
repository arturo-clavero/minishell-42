/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:57:26 by artclave          #+#    #+#             */
/*   Updated: 2024/03/27 03:40:57 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(*original);
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
	free(*str);
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
	free(*str);
	*str = result;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:20:47 by artclave          #+#    #+#             */
/*   Updated: 2024/03/27 14:41:41 by artclave         ###   ########.fr       */
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
static int	check_curly_brackets(char **str, int j)
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
 * @brief evaluates syntax ot determine if $ should be expanded
 * @param curly int = TRUE if '{' found before '$'
 * @param og pointer to string being evaluated prior to any modifications
 * @param start index of '$' + 1
 * @param end pointer of index of end of $variable
 * @return 
 */
static int	should_dollar_expand(int curly, char **og, int start, int *end)
{
	char	*str;

	str = ft_strdup(*og);
	if (curly == TRUE && check_curly_brackets(&str, start) == -1)
		return (-1);
	while (str[*end] && (ft_isalpha(str[*end]) == TRUE
			|| (ft_isalnum(str[*end]) == TRUE && *end > start)
			|| str[*end] == '_'))
		(*end) = (*end) + 1;
	if (str[start] == '\'' || str[start] == '"')
	{
		delete_char_from_str(start - 1, og);
		free(str);
		(*end) = 1;
		return (FALSE);
	}
	if (str[start] == '$' || str[start] == '?')
		(*end)++;
	if (*end - start == 0)
	{
		free(str);
		*end = 0;
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief gets the value that $variable needs to be subtituted with
 * @param original pointer to string being expanded prior to any manipulation
 * @param start index of '$' + 1
 * @param end index of the end of $variable
 * @param ex main structure (all data)
 * @return 
 */
static char	*get_dollar_value(char **original, int start, int end, t_exec *ex)
{
	char	*str;
	char	*value;

	value = NULL;
	str = ft_strdup(*original);
	if (str[start] == '?')
		value = ft_itoa(ex->exit);
	else if (str[start] == '$')
		value = ft_get_pid();
	else
	{
		str[end] = '\0';
		value = ft_strdup(get_env_value(&str[start], ex->env_list));
		if (value)
		{
			delete_char_from_str(0, &value);
			if (ft_strchr(value, '='))
			{
				free(value);
				value = NULL;
			}
		}
	}
	free(str);
	return (value);
}

static char	*get_new_expanded_string(char *str, char *value, char **og, int n)
{
	char	*result;

	if (value)
		result = ft_join_3_strings(str, value, &(*og)[n]);
	else
		result = ft_strdup(str);
	free_data(NULL, str, 1);
	free_data(NULL, value, 1);
	free_data(NULL, *og, 1);
	return (result);
}

/**
 * @brief expands dollar based on syntax rules
 * @param original pointer to string being evaluated prior to any manipulation
 * @param start index of '$' + 1
 * @param ex main structure (all data)
 * @param curly int = TRUE if '{' found before '$', else = FALSE
 * //if ((*original)[start] != '\\')
*	//	result = ft_strjoin(str, &(*original)[end]);
 * @return 
 */
int	expand_dollar(char **original, int start, t_exec *ex, int curly)
{
	int		end;
	char	*value;
	char	*str;

	value = NULL;
	end = start;
	if (should_dollar_expand(curly, original, start, &end) == FALSE)
		return (end);
	str = ft_strdup(*original);
	value = get_dollar_value(original, start, end, ex);
	str[start - 1] = '\0';
	if (value)
		*original = get_new_expanded_string(str, value, original, end);
	else
		*original = get_new_expanded_string(str, value, original, end);
	return (1);
}

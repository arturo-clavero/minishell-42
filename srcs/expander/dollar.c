/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:20:47 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 02:48:55 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief check if quotes are closed
 * @param str srting to check
 * @param n max index to check
 * @return 
 */
int	quotes_are_closed(char	*str, int n)
{
	int	sq;
	int	dq;
	int	i;

	sq = CLOSED;
	dq = CLOSED;
	i = -1;
	while (str[++i] && i < n)
	{
		if ((str[i] == '\'' && dq == OPEN)
			|| (str[i] == '"' && sq == OPEN))
			continue ;
		else if (str[i] == '\'')
			sq ^= 1;
		else if (str[i] == '"')
			dq ^= 1;
	}
	if (dq == CLOSED && sq == CLOSED)
		return (TRUE);
	return (FALSE);
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
		return (free_data((void **)&str, -1));
	while (str[*end] && (ft_isalpha(str[*end]) == TRUE
			|| (ft_isalnum(str[*end]) == TRUE && *end > start)
			|| str[*end] == '_'))
		(*end) = (*end) + 1;
	if (str[start] == '\'' || str[start] == '"')
	{
		(*end) = 0;
		if (quotes_are_closed(str, start - 1) == TRUE)
			delete_char_from_str(start - 1, og);
		return (free_data((void **)&str, FALSE));
	}
	if (str[start] == '$' || str[start] == '?')
		(*end)++;
	if (*end - start == 0 && (!str[*end] || str[*end] == 0))
	{
		*end = 0;
		return (free_data((void **)&str, FALSE));
	}
	return (free_data((void **)&str, TRUE));
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
	char	*temp;

	value = NULL;
	str = ft_strdup(*original);
	if (str[start] == '?')
		value = ft_itoa(g_exit_status);
	else if (str[start] == '$')
		value = ft_get_pid();
	else
	{
		if (end < (int)ft_strlen(str))
			str[end] = '\0';
		temp = ft_strjoin(str, "=\0");
		value = ft_strdup(get_env_value(&temp[start], ex->env_list));
		free_data((void **)&temp, 0);
	}
	free_data((void **)&str, 0);
	return (value);
}

/**
 * @brief join 3 strings to get expanded strings
 * @param str part of string before expanded value
 * @param value expanded value
 * @param og original string
 * @param n index in string where the NOT expanded value ends
 * @return 
 */
static char	*get_new_expanded_string(char *str, char *value, char **og, int n)
{
	char	*result;

	result = ft_join_3_strings(str, value, &(*og)[n]);
	free_data((void **)&str, 1);
	free_data((void **)&value, 1);
	free_data((void **)og, 1);
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
	*original = get_new_expanded_string(str, value, original, end);
	return (1);
}

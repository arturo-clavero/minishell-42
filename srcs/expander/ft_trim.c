/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:57:26 by artclave          #+#    #+#             */
/*   Updated: 2024/03/13 18:25:13 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trim_dollar_substr(char **str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	while ((*str)[i] != '$')
		i++;
	j = i;
	while ((*str)[j] && (*str)[j] != ' ' && (*str)[j] != '\t')
		j++;
	(*str)[i] = '\0';
	result = ft_strjoin(*str, &(*str)[j]);
	free(*str);
	(*str) = result;
	return (0);
}

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

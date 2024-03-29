/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:52:30 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 00:25:27 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Delete a character from a string.
 *
 * @param int delete - The index of the character to delete
 * @param char **str - The string to modify
 * @return void
 */
void	delete_char_from_str(int delete, char **str)
{
	int		len;
	char	*new_str;

	if (!*str)
		return ;
	len = ft_strlen(*str) - 1;
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return ;
	ft_strlcpy(new_str, *str, delete + 1);
	ft_strcat(new_str, &(*str)[delete + 1]);
	free_data((void **)str, 0);
	*str = new_str;
}

/**
 * @brief Add a slash to the inside of double quotes.
 *
 * @param char **str - The string to modify
 * @param int len - The length of the string
 * @return void
 */
void	add_slash_to_inside_double_quotes(char **str, int len)
{
	int		i;
	int		double_quotes;
	char	*new_str;

	double_quotes = 0;
	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '"')
			double_quotes++;
	}
	new_str = (char *)malloc(sizeof(char) * len + double_quotes + 1);
	if (!new_str)
		return ;
	double_quotes = 0;
	i = -1;
	while ((*str)[++i])
	{
		new_str[i + double_quotes] = (*str)[i];
		if ((*str)[i] && (*str)[i + 1] == '"')
			new_str[i + ++double_quotes] = '\\';
	}
	new_str[i + double_quotes] = '\0';
	free_data((void **)str, 0);
	*str = new_str;
}

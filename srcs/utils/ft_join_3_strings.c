/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_3_strings.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:46:38 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 15:51:58 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief joins 3 strings
 * 
 * @param char *str1 - first part of string
 * @param char *str2 - second part of string
 * @param char *str3 - third part of string
 * @return char * - combined string
 */
char	*ft_join_3_strings(char *str1, char *str2, char *str3)
{
	int		len;
	char	*result;

	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	result = (char *)malloc(sizeof(char) * (len + 1));
	ft_strlcpy(result, str1, ft_strlen(str1) + 1);
	ft_strcat(result, str2);
	ft_strcat(result, str3);
	result[len] = '\0';
	return (result);
}

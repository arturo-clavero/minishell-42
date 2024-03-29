/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_strncmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:48:09 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 17:10:45 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ft_strncmp for both lengths of both strings
 *
 * @param char *str1 - first string to compare
 * @param char *str2 - second string to compare
 * @return int - 0 both ft_strncmp are 0, else 1
 */
int	double_strncmp(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (1);
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_numerical.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 02:08:45 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:12:12 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "utils_exec.h"

int	str_is_numerical(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_digit(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

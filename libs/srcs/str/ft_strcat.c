/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 21:48:31 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/07 21:48:56 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Concatenate two strings
 *
 * @param char *dst - The destination string
 * @param char *src - The source string
 * @return void
 */
void	ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dst && dst[i])
		i++;
	j = -1;
	while (src && src[++j])
		dst[i + j] = src[j];
	dst[i + j] = '\0';
}

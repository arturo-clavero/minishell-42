/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libs/srcs/str/ft_strlcpy.c
/*   Created: 2023/08/30 01:05:07 by ugolin-olle       #+#    #+#             */
/*   Updated: 2023/08/30 01:40:16 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
=======
/*   Created: 2023/08/27 17:14:40 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 06:33:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
>>>>>>> origin/execution:libft/ft_strlcpy.c
{
	size_t	i;

	i = 0;
	while (*src && i + 1 < dstsize)
	{
		*dst++ = *src++;
		++i;
	}
	if (i < dstsize)
		*dst = 0;
	while (*src++)
		++i;
	return (i);
}

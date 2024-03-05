/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:libs/srcs/str/ft_strlcat.c
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:52:57 by ugolin-olle       #+#    #+#             */
/*   Updated: 2023/09/11 13:08:13 by ugolin-olle      ###   ########.fr       */
=======
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 07:58:30 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 08:10:50 by artclave         ###   ########.fr       */
>>>>>>> origin/execution:libft/ft_strlcat.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

<<<<<<< HEAD:libs/srcs/str/ft_strlcat.c
size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	total_len;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	total_len = dst_len + src_len;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	i = 0;
	while (src[i] && (dst_len + i + 1) < dstsize)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (total_len);
=======
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
>>>>>>> origin/execution:libft/ft_strlcat.c
}

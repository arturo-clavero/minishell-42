/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libs/srcs/str/ft_strlen.c
/*   Created: 2023/08/28 15:19:51 by ugolin-olle       #+#    #+#             */
/*   Updated: 2023/08/28 15:21:45 by ugolin-olle      ###   ########.fr       */
=======
/*   Created: 2023/08/25 15:52:42 by artclave          #+#    #+#             */
/*   Updated: 2024/02/06 05:56:09 by artclave         ###   ########.fr       */
>>>>>>> origin/execution:libft/ft_strlen.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
<<<<<<< HEAD:libs/srcs/str/ft_strlen.c
	while (s[i])
=======
	while (s && s[i] != '\0')
>>>>>>> origin/execution:libft/ft_strlen.c
		i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libs/srcs/str/ft_toupper.c
/*   Created: 2023/08/30 01:49:13 by ugolin-olle       #+#    #+#             */
/*   Updated: 2023/08/30 01:50:37 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   Created: 2024/01/31 04:30:10 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:11:52 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "utils_exec.h"
>>>>>>> origin/execution:srcs/utils/is_digit.c

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

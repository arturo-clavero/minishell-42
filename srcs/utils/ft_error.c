/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:59:12 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 21:54:27 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_data(char *should_exit, char *data, int exit_code)
{
	free(data);
	if (should_exit)
		exit(exit_code);
	return (exit_code);
}

void	print_error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
}

int	malloc_error(void)
{
	ft_putstr_fd("malloc: Cannot allocate memory", 2);
	return (1);
}

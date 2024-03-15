/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:59:12 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 15:36:59 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief free data
 * 
 * @param char *should exit - if exit
 * @param char *data - data to be freed
 * @param int exit code - return value
 * @return int exit code
 */
int	free_data(char *should_exit, char *data, int exit_code)
{
	free(data);
	if (should_exit)
		exit(exit_code);
	return (exit_code);
}

/**
 * @brief prints errors containing 3 strings 
 * 
 * @param char *str1 - first part of the error message
 * @param char *str2 - second part of the error message
 * @param char *str3 - third part of the error message
 * @return void
 */
void	print_error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
}

/**
 * @brief prints error upon malloc failure
 * 
 * @param void
 * @return int - (1) error code
 */
int	malloc_error(void)
{
	ft_putstr_fd("malloc: Cannot allocate memory", 2);
	return (1);
}

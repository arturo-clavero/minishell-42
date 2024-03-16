/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 09:59:12 by artclave          #+#    #+#             */
/*   Updated: 2024/03/14 18:33:22 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Function to free the data and exit if needed.
 *
 * @param char *should_exit - The string to check if we should exit
 * @param char *data - The data to free
 * @param int exit_code - The exit code
 */
int	free_data(char *should_exit, char *data, int exit_code)
{
	free(data);
	if (should_exit)
		exit(exit_code);
	return (exit_code);
}

/**
 * @brief Function to print an error message.
 *
 * @param char *str1 - The first part of the error message
 * @param char *str2 - The second part of the error message
 * @param char *str3 - The third part of the error message
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
 * @brief Function to print an error message when malloc fails.
 *
 * @return int : 1
 */
int	malloc_error(void)
{
	ft_putstr_fd("malloc: Cannot allocate memory", 2);
	return (1);
}

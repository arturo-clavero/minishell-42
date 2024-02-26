/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:01 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/02/26 10:58:36 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief Exits the program with the specified status after printing the given content to the standard error.
 *
 * @param content The content to be printed to the standard error before exiting. Can be NULL.
 * @param status The exit status of the program.
 */
void	ft_exit(char *content, int status)
{
	if (content)
		ft_putstr_fd(content, STDERR_FILENO);
	exit(status);
}

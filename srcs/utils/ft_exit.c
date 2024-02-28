/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:01 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/02/28 11:08:40 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exit with a message and a status
 *
 * @param char *content - the content to print
 * @param int status - the exit status
 * @return void
 */
void	ft_exit(char *content, int status)
{
	if (content)
		ft_putstr_fd(content, STDERR_FILENO);
	exit(status);
}

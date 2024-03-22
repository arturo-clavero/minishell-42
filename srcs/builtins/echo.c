/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 10:44:48 by artclave          #+#    #+#             */
/*   Updated: 2024/03/22 23:39:41 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the string is a n flag.
 *
 * @param char *str - The string to check
 * @return int
 */
static int	is_nflag(char *str)
{
	int	i;

	i = 0;
	skip_whitespace(str, &i);
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	skip_whitespace(str, &i);
	if (str[i])
		return (0);
	return (1);
}

/**
 * @brief Execute the echo command.
 *
 * @param char **cmd_array - The command array
 * @return int - The exit status
 */
int	exec_echo(char **cmd_array)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	while (cmd_array[++i])
	{
		if (cmd_array[i][0] == '\0')
			continue ;
		if (is_nflag(cmd_array[i]) && n_flag + 1 == i)
		{
			n_flag++;
			continue ;
		}
		printf("%s", cmd_array[i]);
		if (cmd_array[i + 1] != NULL)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}

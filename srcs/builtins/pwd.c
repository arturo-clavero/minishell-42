/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:29:15 by artclave          #+#    #+#             */
/*   Updated: 2024/03/05 11:26:54 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute the pwd command.
 *
 * @param t_exec *ex - The execution structure
 * @return int - The exit status
 */
int	exec_pwd(t_exec *ex)
{
	char	*pwd;

	pwd = get_env_value("PWD=", ex->env_list);
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

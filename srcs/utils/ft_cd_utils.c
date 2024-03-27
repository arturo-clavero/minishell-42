/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:38:10 by artclave          #+#    #+#             */
/*   Updated: 2024/03/27 05:41:05 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief executes cd -
 * @param new_dir pointer to the new directory
 * @param ex main structure (all data)
 */
void	cd_with_dash(char **new_dir, t_exec *ex)
{
	int	i;

	if (!(*new_dir))
		return ;
	i = 0;
	while ((*new_dir)[i] == ' ' || (*new_dir)[i] == '\t')
		i++;
	if ((*new_dir)[i] != '-')
		return ;
	i++;
	while ((*new_dir)[i] == ' ' || (*new_dir)[i] == '\t')
		i++;
	if ((*new_dir)[i])
		return ;
	*new_dir = get_env_value("OLDPWD=", ex->env_list);
}

/**
 * @brief Go back one directory {cd ..} 
 *
 * @param char **new_dir - The new directory
 * @param char *pwd - The current directory
 * @return void
 */
void	cd_with_double_dot(char **new_dir, char *pwd)
{
	int	i;

	if (!(*new_dir))
		return ;
	i = 0;
	while ((*new_dir)[i] == ' ' || (*new_dir)[i] == '\t')
		i++;
	if ((*new_dir)[i] != '.' || (*new_dir)[++i] != '.')
		return ;
	while ((*new_dir)[++i])
	{
		if ((*new_dir)[i] != ' ' && (*new_dir)[i] != '\t')
			return ;
	}
	*new_dir = pwd;
	i = ft_strlen(*new_dir);
	while (--i >= 0)
	{
		if ((*new_dir)[i] == '/')
		{
			(*new_dir)[i] = '\0';
			break ;
		}
	}
}

/**
 * @brief Change the current directory with no arguments.
 *
 * @param char **new_dir - The new directory
 * @param char *pwd - The current directory
 * @return void
 */
void	cd_with_no_arguments(char **new_dir, char *pwd)
{
	int	i;
	int	slash_counter;

	if (*new_dir)
		return ;
	*new_dir = pwd;
	i = -1;
	slash_counter = 0;
	while ((*new_dir)[++i] && slash_counter < 3)
	{
		if ((*new_dir)[i] == '/')
			slash_counter++;
		if (slash_counter == 3)
			(*new_dir)[i] = '\0';
	}
}

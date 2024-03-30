/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 05:38:10 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 16:16:44 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief executes cd -
 * @param new_dir pointer to the new directory
 * @param ex main structure (all data)
 */
void	cd_with_dash(char **new_dir, t_exec *ex, char **og)
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
	if ((*new_dir)[i] && (*new_dir)[i] != 0)
		return ;
	free_data((void **)new_dir, 0);
	*new_dir = ft_strdup(get_env_value("OLDPWD=", ex->env_list));
	free_data((void **)og, 0);
	*og = ft_strdup(*new_dir);
	printf("%s\n", *og);
}

void	get_new_dir_dots(char **new_dir, char *pwd)
{
	int	i;
	int	flag;

	i = ft_strlen(*new_dir);
	flag = 0;
	while (--i >= 0)
	{
		if ((*new_dir)[i] == '/')
		{
			(*new_dir)[i] = '\0';
			if (!(i + 1 < (int)ft_strlen(pwd) - 1 && (*new_dir)[i] == '.')
				&& !(i > 0 && (*new_dir)[i - 1] == '.'))
			{
				if (flag <= 0)
					break ;
				flag -= 100;
			}
			flag += 1;
		}
	}
}

int	cd_double_dot_edge_case(char *pwd, char **new_dir)
{
	if (double_strncmp(pwd, "//") == 0)
	{
		free_data((void **)new_dir, 0);
		*new_dir = ft_strdup(pwd);
		return (TRUE);
	}
	if (double_strncmp(pwd, "/home") == 0 || double_strncmp(pwd, "/home/") == 0)
	{
		free_data((void **)new_dir, 0);
		*new_dir = ft_strdup("/");
		return (TRUE);
	}
	return (FALSE);
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
	if (cd_double_dot_edge_case(pwd, new_dir) == TRUE)
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
	free_data((void **)new_dir, 0);
	*new_dir = ft_strdup(pwd);
	get_new_dir_dots(new_dir, pwd);
}

/**
 * @brief Change the current directory with no arguments.
 *
 * @param char **new_dir - The new directory
 * @param char *pwd - The current directory
 * @return void
 */
void	cd_with_no_arguments(char **new_dir, t_exec *ex)
{
	if (*new_dir)
		return ;
	free_data((void **)new_dir, 0);
	*new_dir = ft_strdup(get_env_value("HOME=", ex->env_list));
}

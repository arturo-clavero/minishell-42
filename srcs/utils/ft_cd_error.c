/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:30:41 by uolle             #+#    #+#             */
/*   Updated: 2024/03/29 17:30:42 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_value_error(char *og, char **new_value, t_exec *ex)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	printf("og: %s\n", og);
	printf("pre\n");
	if (ft_strncmp(og, ".\0", ft_strlen(og)) == 0)
	{
		printf("post a\n");
		free_data((void **)new_value, 0);
		*new_value = ft_strjoin(get_env_value("PWD=", ex->env_list), "/.\0");
	}
	printf("post b\n");
}

int	general_cd_error(char **og, char **buf)
{
	if (errno == ENOENT)
		print_error("cd: ", *og, ": No such file or directory", 0);
	else if (errno == ENOTDIR)
		print_error("cd: ", *og, ": Not a directory", 0);
	else if (errno == EACCES)
		print_error("cd: ", *og, ": Permission denied", 0);
	else if (errno == ELOOP)
		print_error("cd: ", *og, ": Too many symbolic errors", 0);
	else
		print_error("cd: ", *og, ": Unkown error", 0);
	free_data((void **)og, 0);
	return (free_data((void **)buf, 1));
}

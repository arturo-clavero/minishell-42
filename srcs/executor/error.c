/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:29:35 by artclave          #+#    #+#             */
/*   Updated: 2024/03/27 14:55:27 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief prints execution error and exits if command name is incorrect
 * @param str command->array[0]
 * @param ex main structure (all data)
 */
void	execution_cmd_error(char *str, t_exec *ex)
{
	DIR		*dir;

	dir = NULL;
	if (ft_strchr(str, '/'))
	{
		dir = opendir(str);
		if ((dir == NULL && errno == EACCES)
			|| (-1 == access(str, R_OK) && errno == EACCES)
			|| (NULL == fopen(str, "r") && errno == EACCES))
		{
			print_error(str, ": Permission denied", NULL);
			exit (126);
		}
		if (dir != NULL)
		{
			closedir(dir);
			print_error(str, ": Is a directory", NULL);
			exit (126);
		}
		print_error(str, ": No such file or directory", NULL);
	}
	else if (get_env_value("PATH=", ex->env_list))
		print_error(str, ": command not found", NULL);
	else
		print_error(str, ": No such file or directory", NULL);
	exit(127);
}

/**
 * @brief prints execution error and exits if file name is incorrect
 * @param str redir->file_name
 */
int	execution_redir_error(char *str, char **cmd_array)
{
	DIR		*dir;

	dir = NULL;
	if (errno == 13)
	{
		print_error(str, ": Permission denied", NULL);
		return (1);
	}
	if (cmd_array)
		dir = opendir(str);
	if (dir != NULL)
	{
		closedir(dir);
		print_error(str, ": Is a directory", NULL);
	}
	else
		print_error(str, ": No such file or directory", NULL);
	return (1);
}

/**
 * @brief Prints error when expander has issues with curly brackets
 *
 * @param t_cmd *cmd - current command node
 * @return int - error number for potential exit code
 */
int	bad_substitution_error(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->array[++i])
	{
		ft_putstr_fd(cmd->array[i], 2);
		ft_putchar_fd(' ', 2);
	}
	ft_putstr_fd(": bad substitution\n", 2);
	return (1);
}

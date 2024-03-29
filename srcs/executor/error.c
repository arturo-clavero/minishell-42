/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:29:35 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 18:41:46 by artclave         ###   ########.fr       */
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
			exit(print_error(str, ": Permission denied", NULL, 126));
		if (dir != NULL)
		{
			closedir(dir);
			exit(print_error(str, ": Is a directory", NULL, 126));
		}
		exit(print_error(str, ": No such file or directory", NULL, 127));
	}
	else if (get_env_value("PATH=", ex->env_list))
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if (ex->cmd->array[0][0] != 0)
		exit (print_error(str, ": No such file or directory", NULL, 127));
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
		return (print_error(str, ": Permission denied", NULL, 1));
	if (cmd_array)
		dir = opendir(str);
	if (dir != NULL)
	{
		closedir(dir);
		print_error(str, ": Is a directory", NULL, 0);
	}
	else
		print_error(str, ": No such file or directory", NULL, 0);
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

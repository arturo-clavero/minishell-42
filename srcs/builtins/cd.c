/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:04:27 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 15:41:23 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Update the environment variable.
 *
 * @param char *var_name - The name of the variable
 * @param char *new_env - The new value of the variable
 * @param t_exec *ex - The execution structure
 * @return void
 */
static void	update_env(char *var_name, char *new_env, t_exec *ex)
{
	t_list	*env;
	int		len;
	char	*result;

	env = get_env_node(var_name, ex);
	if (env == NULL || new_env == NULL)
		return ;
	len = ft_strlen(var_name) + ft_strlen(new_env);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return ;
	ft_strlcpy(result, var_name, ft_strlen(var_name) + 1);
	ft_strcat(result, new_env);
	env->content = (void *)result;
	add_data_to_cleanup_list((void *)result, &ex->long_term_data);
	return ;
}

/**
 * @brief Deletes last char '/' of a directory.
 *
 * @param char *str - string containing directory
 * @return char *str - modified string
 */
char	*get_new_dir(char *str)
{
	int	i;

	if (!str || str[0] == 0)
		return (NULL);
	if (double_strncmp(str, "//") == 0)
		return ("//\0");
	if (double_strncmp(str, "/") == 0)
		return ("/\0");
	i = ft_strlen(str) - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
		i--;
	if (i >= 0 && str[i] == '/')
		str[i] = '\0';
	return (str);
}

int	change_directories(char **new_dir, char *buf, char *og, t_exec *ex)
{
	char	*new_value;

	new_value = NULL;
	if (chdir(*new_dir) == -1)
		return (general_cd_error(&og, &buf, new_dir));
	new_value = getcwd(new_value, MAX_PATH_LINUX);
	if (new_value == NULL)
		new_value_error(og, &new_value, ex);
	if (ex->cmd->next)
	{
		chdir(buf);
		free_data((void **)new_dir, 0);
		free_data((void **)&og, 0);
		free_data((void **)&new_value, 0);
		return (free_data((void **)&buf, SUCCESS));
	}
	update_env("OLDPWD=", buf, ex);
	update_env("PWD=", new_value, ex);
	if (double_strncmp(*new_dir, "//") == 0)
		update_env("PWD=", *new_dir, ex);
	free_data((void **)&og, 0);
	free_data((void **)new_dir, 0);
	free_data((void **)&new_value, 0);
	return (free_data((void **)&buf, SUCCESS));
}

/**
 * @brief checks if cd has more than one argument
 * @param cmd_array array of strings for current command
 * @return FALSE for incorrect and TRUE for CORRECT
 */
int	max_arguments_ok(char **cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (FALSE);
	}
	if (!cmd_array[1])
		return (TRUE);
	i = ft_strlen(cmd_array[1]);
	if (i > 255)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd_array[1], STDERR_FILENO);
		ft_putstr_fd(": File name too long\n", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Execute the cd command.
 *
 * @param char **cmd_array 
 * @param t_cmd *cmd - The command structure
 * @param t_exec *ex - The execution structure
 * @return int - The exit code
 */
int	exec_cd(char **cmd_array, t_cmd *cmd, t_exec *ex)
{
	char	*buffer;
	char	*new_dir;
	char	*og;

	(void)cmd;
	if (max_arguments_ok(cmd_array) == FALSE)
		return (1);
	if (cmd_array[1] && cmd_array[1][0] == 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * MAX_PATH_LINUX);
	if (!buffer)
		return (malloc_error());
	if (getcwd(buffer, MAX_PATH_LINUX) == NULL)
	{
		free_data((void **)&buffer, 0);
		buffer = ft_strdup(get_env_value("PWD=", ex->env_list));
	}
	og = ft_strdup(cmd_array[1]);
	new_dir = ft_strdup(get_new_dir(cmd_array[1]));
	cd_with_no_arguments(&new_dir, ex);
	cd_with_double_dot(&new_dir, buffer);
	cd_with_dash(&new_dir, ex, &og);
	return (change_directories(&new_dir, buffer, og, ex));
}

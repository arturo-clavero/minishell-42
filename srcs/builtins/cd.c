/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:04:27 by artclave          #+#    #+#             */
/*   Updated: 2024/03/26 06:13:30 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cd_with_tilde(char **new_dir, char *pwd)
{
	int	i;
	int	slash;

	if (!(*new_dir))
		return ;
	i = 0;
	while ((*new_dir)[i] == ' ' || (*new_dir)[i] == '\t')
		i++;
	if ((*new_dir)[i] != '~')
		return ;
	i++;
	while ((*new_dir)[i] == ' ' || (*new_dir)[i] == '\t')
		i++;
	if ((*new_dir)[i])
		return ;
	*new_dir = pwd;
	i = -1;
	slash = 0;
	while ((*new_dir)[++i])
	{
		if ((*new_dir)[i] == '/')
			slash++;
		if (slash == 3)
		{
			(*new_dir)[i] = '\0';
			break ;
		}
	}
}
/**
 * @brief Go back one directory {cd ..} 
 *
 * @param char **new_dir - The new directory
 * @param char *pwd - The current directory
 * @return void
 */
static void	cd_with_double_dot(char **new_dir, char *pwd)
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
static void	cd_with_no_arguments(char **new_dir, char *pwd)
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
	if (env == NULL)
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

	if (!str)
		return (NULL);
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if (str[i] == '/')
		str[i] = '\0';
	return (str);
}

int	change_directories(char *new_dir, char *buf, char *og, t_exec *ex)
{
	if (chdir(new_dir) == -1)
	{
		print_error("cd: ", og, ": No such file or directory");
		free(og);
		return (free_data(NULL, buf, 1));
	}
	free(og);
	if (has_pipe(ex->cmd) == TRUE)
	{
		chdir(buf);
		return (free_data(NULL, buf, SUCCESS));
	}
	update_env("OLD_PWD=", buf, ex);
	update_env("PWD=", getcwd(buf, MAX_PATH_LINUX), ex);
	return (free_data(NULL, buf, SUCCESS));
}

int	max_arguments_ok(char **cmd_array)
{
	int	i;

	i = 0;
	while (cmd_array[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd : too many arguments\n", STDERR_FILENO);
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
 * @param char **cmd_array - The command array
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
		free(buffer);
		buffer = ft_strdup(get_env_value("PWD=", ex->env_list));
	}
	og = ft_strdup(cmd_array[1]);
	new_dir = get_new_dir(cmd_array[1]);
	cd_with_no_arguments(&new_dir, buffer);
	cd_with_double_dot(&new_dir, buffer);
	cd_with_tilde(&new_dir, buffer);
	cd_with_dash(&new_dir, ex);
	return (change_directories(new_dir, buffer, og, ex));
}

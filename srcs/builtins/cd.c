/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 11:04:27 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 21:49:17 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//deletes last char '/'
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

	if (has_pipe(cmd) == TRUE)
		return (0);
	buffer = (char *)malloc(sizeof(char) * MAX_PATH_LINUX);
	if (!buffer)
		return (malloc_error());
	if (getcwd(buffer, MAX_PATH_LINUX) == NULL)
		return (free_data(NULL, buffer, errno));
	update_env("OLD_PWD=", buffer, ex);
	new_dir = get_new_dir(cmd_array[1]);
	new_dir = cmd_array[1];
	cd_with_no_arguments(&new_dir, buffer);
	if (chdir(new_dir) == -1)
	{
		print_error("cd: ", new_dir, ": No such file or directory");
		return (free_data(NULL, buffer, 1));
	}
	update_env("PWD=", getcwd(buffer, MAX_PATH_LINUX), ex);
	return (free_data(NULL, buffer, SUCCESS));
}

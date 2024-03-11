/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:47:14 by artclave          #+#    #+#             */
/*   Updated: 2024/03/05 11:17:14 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the command is a builtin
 *
 * @param char *cmd - The command to check
 * @return int - TRUE if the command is a builtin, FALSE otherwise
 */
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (TRUE);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0
			&& ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Execute the builtin command
 *
 * @param t_cmd cmd - The command to execute
 * @param t_exec *ex - The execution structure
 */
void	execute_builtin(t_cmd *cmd, t_exec *ex)
{
	int	exit_code;

	ex->is_builtin_last = FALSE;
	if (ft_strncmp(cmd->array[0], "cd", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "cd", ft_strlen("cd")) == 0)
		exit_code = exec_cd(cmd->array, cmd, ex);
	else if (ft_strncmp(cmd->array[0], "echo", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "echo", ft_strlen("echo")) == 0)
		exit_code = exec_echo(cmd->array);
	else if (ft_strncmp(cmd->array[0], "env", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "env", ft_strlen("env")) == 0)
		exit_code = exec_env(ex);
	else if (ft_strncmp(cmd->array[0], "exit", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "exit", ft_strlen("exit")) == 0)
		exit_code = exec_exit(cmd->array, cmd, ex);
	else if (ft_strncmp(cmd->array[0], "export", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "export", ft_strlen("export")) == 0)
		exit_code = exec_export(cmd->array, ex);
	else if (ft_strncmp(cmd->array[0], "pwd", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "pwd", ft_strlen("pwd")) == 0)
		exit_code = exec_pwd(ex);
	else if (ft_strncmp(cmd->array[0], "unset", ft_strlen(cmd->array[0])) == 0
			&& ft_strncmp(cmd->array[0], "unset", ft_strlen("unset")) == 0)
		exit_code = exec_unset(cmd->array, ex);
	if (!cmd->next)
	{
		ex->is_builtin_last = TRUE;
		ex->exit = exit_code;
	}
}

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
 * @brief ft_strncmp for both lengths of both strings
 *
 * @param char *str1 - first string to compare
 * @param char *str2 - second string to compare
 * @return int - 0 both ft_strncmp are 0, else 1
 */
static int	double_strncmp(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (0);
	return (1);
}

/**
 * @brief Check if the command is a builtin
 *
 * @param char *cmd - The command to check
 * @return int - TRUE if the command is a builtin, FALSE otherwise
 */
int	is_builtin(char *cmd)
{
	if (double_strncmp(cmd, "cd") == 0)
		return (TRUE);
	else if (double_strncmp(cmd, "echo") == 0)
		return (TRUE);
	else if (double_strncmp(cmd, "env") == 0)
		return (TRUE);
	else if (double_strncmp(cmd, "exit") == 0)
		return (TRUE);
	else if (double_strncmp(cmd, "export") == 0)
		return (TRUE);
	else if (double_strncmp(cmd, "pwd") == 0)
		return (TRUE);
	else if (double_strncmp(cmd, "unset") == 0)
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
	if (are_redirections_valid(cmd) == EXIT_FAILURE)
		return ;
	if (double_strncmp("cd", cmd->array[0]) == 0)
		exit_code = exec_cd(cmd->array, cmd, ex);
	else if (double_strncmp("echo", cmd->array[0]) == 0)
		exit_code = exec_echo(cmd->array);
	else if (double_strncmp("env", cmd->array[0]) == 0)
		exit_code = exec_env(ex);
	else if (double_strncmp("exit", cmd->array[0]) == 0)
		exit_code = exec_exit(cmd->array, cmd, ex);
	else if (double_strncmp("export", cmd->array[0]) == 0)
		exit_code = exec_export(cmd->array, ex);
	else if (double_strncmp("pwd", cmd->array[0]) == 0)
		exit_code = exec_pwd(ex);
	else if (double_strncmp("unset", cmd->array[0]) == 0)
		exit_code = exec_unset(cmd->array, ex);
	if (!cmd->next)
	{
		ex->is_builtin_last = TRUE;
		ex->exit = exit_code;
	}
}

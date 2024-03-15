/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 06:22:23 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 14:53:27 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the cmd path for exec object
 *
 * @param char **cmd_array - The command array
 * @param char **env - The environment
 * @return char* - The command path
 */
static char	*get_cmd_path_for_exec(char **cmd_array, char **env)
{
	char	*test_path;
	int		i;

	i = -1;
	if (access(cmd_array[0], F_OK | X_OK) == 0)
		return (cmd_array[0]);
	while (env[++i] != NULL)
	{
		test_path = ft_strjoin_with_sep(env[i], cmd_array[0], '/');
		if (access(test_path, F_OK | X_OK) == 0)
			return (test_path);
		else
			free(test_path);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_array[0], 2);
	if (ft_strchr(cmd_array[0], '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
	exit(127);
	return (NULL);
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

/**
 * @brief Checks if current command string is a directory
 * instead of a command
 * 
 * @param t_cmd *cmd - current command node
 * @return void
 */
static void	check_if_cmd_is_directory(t_cmd *cmd)
{
	struct stat	cmd_stat;

	stat(cmd->array[0], &cmd_stat);
	if (S_ISDIR(cmd_stat.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->array[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(1);
	}
}

/**
 * @brief Execute the command.
 *
 * @param int id - The id
 * @param int curr_cmd - The current command
 * @param t_cmd *cmd - The command
 * @param t_exec *ex - The execution
 * @return void
 */
void	execute_command(int id, int curr_cmd, t_cmd *cmd, t_exec *ex)
{
	char		*cmd_path;
	char		**env;

	id = fork();
	if (id == -1)
		return ;
	if (id == 0)
	{
		close_open_pipes(curr_cmd, ex);
		if (cmd->bad_substitution == TRUE)
			exit (bad_substitution_error(cmd));
		if (are_redirections_valid(cmd) == EXIT_FAILURE)
			exit(1);
		if (ft_strncmp(cmd->array[0], "./minishell",
				ft_strlen(cmd->array[0])) == 0)
			env = ft_list_to_str_array(ex->env_list);
		else
			env = ft_split(get_env_value("PATH=", ex->env_list), ':');
		cmd_path = get_cmd_path_for_exec(cmd->array, env);
		check_if_cmd_is_directory(cmd);
		execve(cmd_path, cmd->array, env);
		perror(cmd->array[0]);
		exit(127);
	}
}

/**
 * @brief Wait for child exit status.
 *
 * @param t_exec *ex - The execution structure.
 * @return void
 */
void	wait_for_child_exit_status(t_exec *ex)
{
	int	exit_status;
	int	child_exit;
	int	curr_child;

	curr_child = -1;
	while (++curr_child < ex->total_children)
	{
		waitpid(ex->id[curr_child], &exit_status, 0);
		if (WIFEXITED(exit_status))
			child_exit = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			child_exit = WTERMSIG(exit_status);
		if (ex->is_builtin_last == FALSE)
			ex->exit = child_exit;
	}
	if (ex->exit == 13)
		ex->exit = 127;
}

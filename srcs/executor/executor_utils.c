/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 06:22:23 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 16:04:55 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief extract array of strings from PATH env variable
 * @param env environment strings
 * @return char *- array of strings with all paths
 */
static char	**get_all_paths(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i])
		return (ft_split(&env[i][5], ':'));
	return (NULL);
}

/**
 * @brief Get the cmd path for exec object
 *
 * @param char **cmd_array - The command array
 * @param char **env - The environment
 * @return char* - The command path
 */
static char	*get_cmd_path_for_exec(char **cmd_array, char **env, t_exec *ex)
{
	char	**all_paths;
	char	*test_path;
	int		i;

	test_path = NULL;
	if (access(cmd_array[0], F_OK | X_OK) == 0)
		return (cmd_array[0]);
	all_paths = get_all_paths(env);
	i = -1;
	while (all_paths && all_paths[++i])
	{
		test_path = ft_join_3_strings(all_paths[i], "/", cmd_array[0]);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free_data((void **)&test_path, 0);
	}
	i = -1;
	while (all_paths && all_paths[++i])
		free_data((void **)&all_paths[i], 0);
	free_data((void **)&all_paths, 0);
	if (test_path)
		return (test_path);
	execution_cmd_error(cmd_array[0], ex);
	return (NULL);
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
void	execute_command(int *id, int curr_cmd, t_cmd *cmd, t_exec *ex)
{
	char	*cmd_path;
	char	**env;

	*id = fork();
	if (*id == -1)
		return ;
	if (*id == 0)
	{
		close_open_pipes(curr_cmd, ex);
		if (cmd->bad_substitution == TRUE)
			exit(bad_substitution_error(cmd));
		if (are_redirections_valid(cmd) == EXIT_FAILURE)
			exit(1);
		env = ft_list_to_str_array(ex->env_list);
		cmd_path = get_cmd_path_for_exec(cmd->array, env, ex);
		execve(cmd_path, cmd->array, env);
		execution_cmd_error(cmd->array[0], ex);
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
		if (ex->is_builtin_last == FALSE && curr_child
			+ 1 == ex->total_children)
			g_exit_status = child_exit;
	}
	if (g_exit_status == 13)
		g_exit_status = 127;
}

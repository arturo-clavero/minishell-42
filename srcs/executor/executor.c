/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:24:40 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/15 14:23:13 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process the commands.
 *
 * @param t_cmd *cmd - The command
 * @param t_exec *ex - The execution
 * @return void
 */
void	process_cmds(t_cmd *cmd, t_exec *ex)
{
	int	curr_cmd;
	int	curr_child;

	curr_cmd = 0;
	curr_child = 0;
	while (cmd)
	{
		save_original_io(ex);
		dup_pipes(curr_cmd, cmd, ex);
		if (is_builtin(cmd->array[0]) == TRUE)
		{
			if (are_redirections_valid(cmd) == EXIT_SUCCESS)
				execute_builtin(cmd, ex);
			else if (!cmd->next)
				ex->exit = 1;
		}
		else
		{
			execute_command(ex->id[curr_child], curr_cmd, cmd, ex);
			curr_child++;
		}
		curr_cmd++;
		reset_io(ex);
		cmd = cmd->next;
	}
}

/**
 * @brief Execute the execution command.
 *
 * @param t_exec *ex - The execution structure.
 * @return void
*/
void	execution_main(t_cmd *cmd, t_exec *ex)
{
	initialize_execution(cmd, ex);
	create_pipes(cmd, ex);
	create_child_ids(cmd, ex);
	process_cmds(cmd, ex);
	wait_for_child_exit_status(ex);
	close_all_pipes(ex);
	maybe_quit_program(ex);
	clean_list(ex->short_term_data, TRUE);
	clean_t_cmd(ex->cmd);
}

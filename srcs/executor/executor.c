/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:24:40 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/07 10:25:01 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute the execution command.
 *
 * @param t_exec *ex - The execution structure.
 * @return void
*/
void	execution_main(t_cmd *cmd, t_exec *ex)
{
	ex->cmd = cmd;
	ex->short_term_data = NULL;
	handle_dollar_sign(&ex->cmd, ex);
	create_pipes(cmd, ex);
	create_child_ids(cmd, ex);
	process_cmds(cmd, ex);
	wait_for_child_exit_status(ex);
	adjust_shlvl(cmd, ex);
	maybe_quit_program(ex);
	clean_list(ex->short_term_data, TRUE);
	clean_t_cmd(ex->cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:24:40 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/27 14:55:05 by ugolin-olle      ###   ########.fr       */
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
	curr_child = -1;
	while (cmd)
	{
		save_original_io(ex);
		dup_pipes(curr_cmd, cmd, ex);
		if (cmd->array && is_builtin(cmd->array[0]) == TRUE)
		{
			if (are_redirections_valid(cmd) == EXIT_SUCCESS)
				execute_builtin(cmd, ex);

			else if (!cmd->next)
				g_exit_status = 1;
		}
		else if (cmd->array && ++curr_child > -1)
			execute_command(&ex->id[curr_child], curr_cmd, cmd, ex);
		else
		{
			are_redirections_valid(cmd);
		}
		curr_cmd++;
		reset_io(ex);
		cmd = cmd->next;
	}
}

void	realloc_cmd_array(char ***arr, int i)
{
	int		n;
	char	**result;

	n = 0;
	while ((*arr)[n])
		n++;
	n -= i;
	result = (char **)malloc(sizeof(char *) * (n + 1));
	if (!result)
		return ;
	n = -1;
	while ((*arr)[i])
	{
		result[++n] = ft_strdup((*arr)[i]);
		i++;
	}
	result[++n] = NULL;
	n = -1;
	while ((*arr)[++n])
		free((*arr)[n]);
	free(*arr);
	*arr = result;
}

int	empty_cmd(t_cmd *cmd, t_exec *ex)
{
	int	i;
	int	empty;

	empty = TRUE;
	while (empty && cmd)
	{
		i = -1;
		while (empty && cmd->array && cmd->array[++i])
		{
				if (cmd->array[i][0] == 0)
				{
					if (empty && cmd->array[++i] == NULL)
					{
						clean_t_cmd(ex->cmd, ex);
						g_exit_status = 0;
						return (TRUE);
					}
					else
					{
						realloc_cmd_array(&cmd->array, i);
						return (empty_cmd(cmd, ex));
					}
				}
				else
					empty = FALSE;
		}
		cmd = cmd->next;
	}
	return (empty);
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
	if (!cmd)
		return ;
	create_pipes(cmd, ex);
	create_child_ids(cmd, ex);
	process_cmds(cmd, ex);
	wait_for_child_exit_status(ex);
	close_all_pipes(ex);
	maybe_quit_program(ex);
	clean_list(ex->short_term_data, TRUE);
	clean_t_cmd(ex->cmd, ex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 07:03:24 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 12:10:14 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Save the original input and output.
 *
 * @param t_exec *ex - The execution
 * @return void
*/
void	save_original_io(t_exec *ex)
{
	ex->stdin_original = dup(STDIN_FILENO);
	ex->stdout_original = dup(STDOUT_FILENO);
}

/**
 * @brief Reset the input and output.
 *
 * @param t_exec *ex - The execution
 * @return void
*/
void	reset_io(t_exec *ex)
{
	t_redir	*redir;

	dup2(ex->stdin_original, STDIN_FILENO);
	close(ex->stdin_original);
	dup2(ex->stdout_original, STDOUT_FILENO);
	close(ex->stdout_original);
	if (!ex->cmd || !ex->cmd->array || ex->cmd->array[0] || ex->cmd->array[0][0] == 0)
		return ;
	if (double_strncmp(ex->cmd->array[0], "exit") || ex->cmd->next)
		return ;
	redir = ex->cmd->redir;
	while (redir)
	{
		if (redir->type == PIPE)
			return ;
		redir = redir->next;
	}
	printf("exit\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:srcs/executor/execution/input_output.c
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 07:03:24 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:18:07 by artclave         ###   ########.fr       */
========
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:42:49 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:11:30 by artclave         ###   ########.fr       */
>>>>>>>> origin/execution:srcs/utils/builtin_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
<<<<<<<< HEAD:srcs/executor/execution/input_output.c
#include "process_exec.h"

void	save_original_io(t_exec *ex)
{
	ex->stdin_original = dup(STDIN_FILENO);
	ex->stdout_original = dup(STDOUT_FILENO);
}

void	reset_io(t_exec *ex)
{
	dup2(ex->stdin_original, STDIN_FILENO);
	close(ex->stdin_original);
	dup2(ex->stdout_original, STDOUT_FILENO);
	close(ex->stdout_original);
========
#include "utils_exec.h"

int	has_pipe(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == PIPE)
			return (TRUE);
		redir = redir->next;
	}
	return (FALSE);
>>>>>>>> origin/execution:srcs/utils/builtin_utils.c
}

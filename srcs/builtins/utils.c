/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:10:30 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/09 14:49:49 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the command has a pipe.
 *
 * @param t_cmd *cmd - The command structure
 * @return int - TRUE if the command has a pipe, FALSE otherwise
*/
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
}

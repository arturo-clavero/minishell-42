/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:srcs/utils/builtin_utils.c
/*   Created: 2024/02/11 13:42:49 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:11:30 by artclave         ###   ########.fr       */
========
/*   Created: 2024/01/31 04:30:13 by artclave          #+#    #+#             */
/*   Updated: 2024/02/13 09:11:56 by artclave         ###   ########.fr       */
>>>>>>>> origin/execution:srcs/utils/is_letter.c
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
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
}
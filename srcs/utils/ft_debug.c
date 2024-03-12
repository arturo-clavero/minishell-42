/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:55:57 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 22:59:50 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Print t_cmd structure.
 *
 * @param t_cmd *cmd - The t_cmd structure
 * @return void
 */
void	ft_print_cmd(t_cmd *cmd)
{
	int		i;
	t_redir	*redir;

	while (cmd)
	{
		printf("Command array:\n");
		i = 0;
		while (cmd->array[i])
		{
			printf("array[%d] = %s\n", i, cmd->array[i]);
			i++;
		}
		printf("Redirections:\n");
		redir = cmd->redir;
		while (redir)
		{
			printf("type = %d, file_name = %s, heredoc_buff = %s, duplication = %d\n", redir->type, redir->file_name, redir->heredoc_buff,
				redir->duplication);
			redir = redir->next;
		}
		cmd = cmd->next;
		printf("\n");
	}
}

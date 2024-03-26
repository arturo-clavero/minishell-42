/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:45:11 by artclave          #+#    #+#             */
/*   Updated: 2024/03/24 19:27:38 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief malloc array of integers to hold children process ids
 * 
 * @param t_cmd *cmd - command list
 * @param t_exec *ex - exec structure
 * @return void
 */
void	create_child_ids(t_cmd *cmd, t_exec *ex)
{
	int	i;

	ex->total_children = 0;
	ex->id = NULL;
	while (cmd)
	{
		if (cmd->array && is_builtin(cmd->array[0]) == FALSE)
			ex->total_children++;
		cmd = cmd->next;
	}
	if (ex->total_children == 0)
		return ;
	ex->id = (int *)malloc(sizeof(int) * ex->total_children);
	if (!ex->id)
		return ;
	i = -1;
	while (++i < ex->total_children)
		ex->id[i] = -1;
	add_data_to_cleanup_list((void *)ex->id, &ex->short_term_data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:20:27 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 16:13:51 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	Initializes exec structure at the beginning of each ./minishell call 
 * 
 * @param t_exec *ex - exec structure
 * @param char **env - enviroments array of strings from main
 * @return void
 */

void	initialize_minishell(t_exec *ex, char **env)
{
	int	i;

	ex->cmd = NULL;
	ex->env_list = NULL;
	ex->short_term_data = NULL;
	ex->long_term_data = NULL;
	ex->total_pipes = 0;
	ex->total_children = 0;
	ex->is_builtin_last = FALSE;
	ex->fd = NULL;
	ex->id = NULL;
	ex->exit = 0;
	i = -1;
	while (env && env[++i])
		new_node((void *)env[i], &ex->env_list);
	change_shlvl(1, ex);
}

/**
 * @brief Initializes exec structure at the beginning of each execution call
 * 
 * @param t_cmd *cmd - command list
 * @param t_exec *ex - exec structure
 * @return void
 */
void	initialize_execution(t_cmd *cmd, t_exec *ex)
{
	ex->cmd = cmd;
	ex->short_term_data = NULL;
	ex->total_pipes = 0;
	ex->total_children = 0;
	ex->is_builtin_last = FALSE;
	ex->fd = NULL;
	ex->id = NULL;
}

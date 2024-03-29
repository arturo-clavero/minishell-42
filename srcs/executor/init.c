/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:20:27 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 17:16:43 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ex->stdin_original = STDIN_FILENO;
	ex->stdout_original = STDOUT_FILENO;
}

/**
 * @brief Initialize the minishell.
 *
 * @param t_exec *ex - The minishell object.
 * @param char **env - The environment variables list.
 * @return void
 */
void	initialize_minishell(t_exec *ex, char **env)
{
	int	i;

	ex->cmd = NULL;
	ex->env = env;
	ex->env_list = NULL;
	ex->short_term_data = NULL;
	ex->long_term_data = NULL;
	ex->total_pipes = 0;
	ex->total_children = 0;
	ex->is_builtin_last = FALSE;
	ex->fd = NULL;
	ex->id = NULL;
	g_exit_status = 0;
	i = -1;
	while (env && env[++i])
		new_node((void *)env[i], &ex->env_list);
	change_shlvl(1, ex);
}

/**
 * @brief Initialize parsing part.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
void	initialize_parsing(t_exec *ex)
{
	ex->args = NULL;
	ex->lexer = ft_init_lexer();
}

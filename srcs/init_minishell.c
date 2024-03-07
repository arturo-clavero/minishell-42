/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:15:24 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/07 11:15:33 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_minishell(t_exec *ex, char **env)
{
	int		i;
	int		shlvl;

	ex->cmd = NULL;
	ex->env_list = NULL;
	ex->short_term_data = NULL;
	ex->long_term_data = NULL;
	ex->program_path = NULL;
	ex->total_pipes = 0;
	ex->total_children = 0;
	ex->is_builtin_last = FALSE;
	ex->fd = NULL;
	ex->id = NULL;
	ex->exit = 0;
	ex->shell_env_list = NULL;
	i = -1;
	while (env[++i])
	{
		new_node((void *)env[i], &ex->env_list);
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			ex->program_path = &env[i][4];
	}
	shlvl = change_shlvl(0, ex);
	change_shlvl(2 - shlvl, ex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   innit_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 05:37:59 by artclave          #+#    #+#             */
<<<<<<<< HEAD:srcs/executor/prep_execution/innit_minishell.c
/*   Updated: 2024/02/28 10:36:50 by ugolin-olle      ###   ########.fr       */
========
/*   Updated: 2024/02/13 09:17:25 by artclave         ###   ########.fr       */
>>>>>>>> origin/execution:srcs/prep_execution/innit_minishell.c
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "prep_exec.h"
#include "post_exec.h"
#include "utils_exec.h"

void	initialize_minishell(t_exec *ex, char **env)
{
<<<<<<<< HEAD:srcs/executor/prep_execution/innit_minishell.c
========
	int		i;
>>>>>>>> origin/execution:srcs/prep_execution/innit_minishell.c
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
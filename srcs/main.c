/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:11:21 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 00:46:13 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prompt the user for a command and execute it.
 *
 * @param void
 * @return char * The command entered by the user.
 */

static char	*ft_prompt_display(void)
{
	char	*line;

	line = readline(RED "[MINISHELL] $> " RESET);
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

/**
 * @brief Relaunch the minishell.
 *
 * @param t_exec *ex - The execution structure.
 * @return void
 */
void	ft_relaunch_minishell(t_exec *ex)
{
	ft_free_lexer(ex);
	clean_list(ex->env_list, FALSE);
	clean_list(ex->short_term_data, TRUE);
	clean_list(ex->long_term_data, TRUE);
	initialize_minishell(ex, ex->env);
	initialize_execution(ex->cmd, ex);
	ft_launch_minishell(ex);
}

/**
 * @brief Launch minishell.
 *
 * @param t_exec *ex - The execution structure.
 * @return void
 */
void	ft_launch_minishell(t_exec *ex)
{
	char	*line;

	while (1)
	{
		line = ft_prompt_display();
		if (!line)
			continue ;
		ex->args = line;
		ft_lexer(ex);
		ft_parser(ex);
		free(line);
		expand_each_cmd_node(&ex->cmd, ex);
		execution_main(ex->cmd, ex);
		ft_relaunch_minishell(ex);
	}
}

/**
 * @brief Launch the minishell.
 *
 * @param int argc - The number of arguments
 * @param char **argv - The arguments list
 * @param char **env - The environment variables list
 * @return int 0 if success, 1 if error.
 */

int	main(int argc, char **argv, char **env)
{
	t_exec	ex;

	if (argc != 1 || argv[0] == NULL)
	{
		printf(ERROR_NO_ARGS);
		return (1);
	}
	initialize_minishell(&ex, env);
	initialize_execution(ex.cmd, &ex);
	ft_launch_minishell(&ex);
	return (0);
}

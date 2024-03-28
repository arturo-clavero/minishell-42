/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:11:21 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/28 13:54:22 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prompt the user for a command and execute it.
 *
 * @param void
 * @return char * The command entered by the user.
 */
static char	*ft_prompt_display(t_exec *ex)
{
	char	*line;
	char	*prompt;
	char	*temp;

	prompt = ft_strjoin(RED "[MINISHELL]:" BLUE, get_env_value("PWD=",
				ex->env_list));
	temp = ft_strjoin(prompt, " $> " RESET);
	free_data(NULL, (void *)prompt, -2);
	prompt = temp;
	line = readline(prompt);
	free_data(NULL, (void *)prompt, -2);
	if (!line)
		exit(g_exit_status);
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
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
		line = ft_prompt_display(ex);
		if (!line)
			continue ;
		initialize_parsing(ex);
		ex->args = line;
		ft_lexer(ex);
		ft_parser(ex->lexer, ex);
		free_data(NULL, (void *)line, 0);
		ft_free_lexer(ex);
		heredoc(ex);
		expand_each_cmd_node(&ex->cmd, ex);
		quotes(ex->cmd, ex);
		execution_main(ex->cmd, ex);
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
	ft_init_signals();
	ft_launch_minishell(&ex);
	return (g_exit_status);
}

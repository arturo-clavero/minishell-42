/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:11:21 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/27 14:55:43 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

/**
 * @brief Prompt the user for a command and execute it.
 *
 * @param void
 * @return char * The command entered by the user.
 */

static char	*ft_prompt_display(void)
{
	char	*line;
	char	*prompt;

	prompt = ft_strjoin(RED "[MINISHELL]:" BLUE, getcwd(NULL, 0));
	prompt = ft_strjoin(prompt, " $> " RESET);
	line = readline(prompt);
	free(prompt);
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
		line = ft_prompt_display();
		if (!line)
			continue ;
		initialize_parsing(ex);
		ex->args = line;
		ft_lexer(ex);
		ft_parser(ex->lexer, ex);
		free(line);
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
	return (0);
}

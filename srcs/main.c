/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:11:21 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/13 12:47:44 by ugolin-olle      ###   ########.fr       */
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

	printf(BLUE "[MINISHELL]:" RED "%s$ " RESET, getcwd(NULL, 0));
	line = readline("");
	if (ft_strlen(line) > 0)
		add_history(line);
	rl_forced_update_display();
	return (line);
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
	char	*line;

	if (argc != 1 || argv[0] == NULL)
	{
		printf("Error: Invalid arguments.\n");
		return (1);
	}
	initialize_minishell(&ex, env);
	while (1)
	{
		line = ft_prompt_display();
		if (!line)
			continue ;
		ex.args = line;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:11:21 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/12 10:13:51 by ugolin-olle      ###   ########.fr       */
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

	struct termios old_term, new_term;
	tcgetattr(STDIN_FILENO, &old_term);
	new_term = old_term;
	new_term.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	printf(BLUE "[MINISHELL]:" RED "%s$ " RESET, getcwd(NULL, 0));
	line = readline("");
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	if (line != NULL)
		if (ft_strlen(line) > 0)
			add_history(line);
	return (line);
}

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
		if (line == NULL)
			ft_prompt_display();
		ex.args = line;
		ex.cmd = ft_parse_input(ex.args);
	}
	return (0);
}

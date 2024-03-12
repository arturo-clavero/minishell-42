/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:23:10 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 23:25:01 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parse the input string
 *
 * @param char *str - The input string
 * @return t_cmd* : The command list
 */
t_cmd	*ft_parse_input(char *str)
{
	t_cmd	*cmd;
	t_lexer	*lexer;
	int		i;
	t_lexer	*new_lexer;

	i = 0;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	lexer = NULL;
	while (str[i])
	{
		new_lexer = (t_lexer *)malloc(sizeof(t_lexer));
		new_lexer->next = lexer;
		lexer = new_lexer;
		if (ft_lexer(str, i, &lexer) == -1)
		{
			free(cmd);
			return (NULL);
		}
		i++;
	}
	return (cmd);
}

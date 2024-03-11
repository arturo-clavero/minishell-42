/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:23:10 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 12:23:32 by ugolin-olle      ###   ########.fr       */
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
	t_lexer	*lexer;
	t_cmd	*cmd;
	int		i;

	lexer = NULL;
	cmd = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_lexer(str, i, &lexer) == -1)
			return (NULL);
		printf("Token: %d\n", lexer->token);
		i++;
	}
	return (cmd);
}

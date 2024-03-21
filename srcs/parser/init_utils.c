/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:21:43 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/21 12:28:13 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief mallocs string array for a command node
 *
 * @param t_lexer *lexer - Node containing the first string of the command array
 * @return char ** - malloc'd array
 */
char	**ft_malloc_node_array(t_lexer *lexer)
{
	int	n;

	n = 0;
	while (lexer && lexer->token != 2)
	{
		if (lexer->str && lexer->token == 1)
			n++;
		lexer = lexer->next;
	}
	return ((char **)malloc(sizeof(char *) * (n + 1)));
}

/**
 * @brief adds a node to the end of command list
 *
 * @param t_cmd *node, new node to be added
 * @param t_cmd **cmd, pointer to command list
 * @return void
 */
void	ft_add_cmd_node_to_list(t_cmd *node, t_cmd **cmd)
{
	t_cmd	*temp;

	if (*cmd == NULL)
		*cmd = node;
	else
	{
		temp = *cmd;
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

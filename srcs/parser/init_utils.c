/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:21:43 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/23 15:20:40 by artclave         ###   ########.fr       */
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
	int	flag_file;

	n = 0;
	flag_file = FALSE;
	while (lexer && lexer->token != 2)
	{
		if (lexer->token != WORD && lexer->token != PIPE)
			flag_file = TRUE;
		else if (lexer->str && lexer->token == 1 && flag_file == FALSE)
			n++;
		else if (flag_file == TRUE)
			flag_file = FALSE;
		lexer = lexer->next;
	}
	if (n == 0)
		return (NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:39:09 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/23 01:56:15 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief The main function for the paser.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
void	ft_parser(t_lexer *lexer, t_exec *ex)
{
	t_cmd	*node;

	node = ft_init_cmd();
	if (!node)
		return ;
	node->bad_substitution = 0;
	node->redir = NULL;
	node->next = NULL;
	node->array = ft_malloc_node_array(lexer);
	ft_add_cmd(&node, lexer, ex);
}

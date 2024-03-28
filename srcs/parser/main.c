/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:39:09 by ugolin-olle       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/28 13:56:45 by uolle            ###   ########.fr       */
=======
/*   Updated: 2024/03/28 14:08:59 by artclave         ###   ########.fr       */
>>>>>>> origin/master
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

	ft_check_syntax(ex);
	ft_debug_lexer(ex->lexer);
	node = ft_init_cmd();
	if (!node)
		return ;
	node->bad_substitution = 0;
	node->redir = NULL;
	node->next = NULL;
	node->array = ft_malloc_node_array(lexer);
	ft_add_cmd(&node, lexer, ex);
}

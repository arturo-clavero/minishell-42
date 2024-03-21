/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:56:02 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/21 18:26:01 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize the lexer.
 *
 * @param void
 * @return t_lexer* The new lexer.
 */
t_lexer	*ft_init_lexer(void)
{
	t_lexer	*new_lexer;

	new_lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new_lexer)
		return (NULL);
	new_lexer->str = NULL;
	new_lexer->token = UNINITIALIZED;
	new_lexer->next = NULL;
	new_lexer->prev = NULL;
	return (new_lexer);
}

/**
 * @brief Add a new lexer to the list.
 *
 * @param char *str - The string to add to the lexer.
 * @param t_token_type type - The token to add to the lexer.
 * @param t_lexer *lexer - The lexer list.
 * @return int - 1 if success, 0 if error.
 */
int	ft_add_lexer(char *str, t_token_type type, t_lexer *lexer)
{
	t_lexer	*node;
	t_lexer	*tmp;

	if (lexer->str == NULL && lexer->token == UNINITIALIZED)
	{
		lexer->str = str;
		lexer->token = type;
		return (1);
	}
	node = ft_init_lexer();
	if (!node)
		return (0);
	node->str = str;
	node->token = type;
	tmp = lexer;
	if (tmp == NULL)
	{
		lexer = node;
		return (0);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->prev = tmp;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:54:56 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/27 22:06:15 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new node.
 *
 * @param void *content - The content
 * @param t_list **list - The list
 * @return void
 */
void	new_node(void *content, t_list **list)
{
	t_list	*new_node;
	t_list	*prev_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = content;
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		prev_node = get_last_node(*list);
		prev_node->next = new_node;
	}
}

/**
 * @brief Get the last node.
 *
 * @param t_list *list - The list
 * @return t_list*
 */
t_list	*get_last_node(t_list *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}

/**
 * @brief Add data to the cleanup list.
 *
 * @param void *content - The content
 * @param t_list **list - The list
 * @return void
 */
void	add_data_to_cleanup_list(void *content, t_list **list)
{
	t_list	*node;

	node = NULL;
	if (!content)
		return ;
	new_node(content, &node);
	node->next = (*list);
	(*list) = node;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_str_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:14:35 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 15:53:17 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief list to string array
 * 
 * @param t_list *lst - list to be transformed
 * @return char ** - array of strings, where each string is = node->content
 */
char	**ft_list_to_str_array(t_list *lst)
{
	int		n;
	t_list	*head;
	char	**result;
	int		i;

	head = lst;
	n = 0;
	while (lst)
	{
		if (ft_strchr((char *)lst->content, '='))
			n++;
		lst = lst->next;
	}
	result = (char **)malloc(sizeof(char *) * (n + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (head)
	{
		if (ft_strchr((char *)head->content, '='))
			result[++i] = ft_strdup((char *)head->content);
		head = head->next;
	}
	result[++i] = NULL;
	return (result);
}

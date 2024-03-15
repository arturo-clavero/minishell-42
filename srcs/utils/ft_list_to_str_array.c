/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_str_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 23:14:35 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 08:08:04 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	lst = head;
	i = -1;
	while (lst)
	{
		if (ft_strchr((char *)lst->content, '='))
			result[++i] = ft_strdup((char *)lst->content);
		lst = lst->next;
	}
	result[++i] = NULL;
	return (result);
}
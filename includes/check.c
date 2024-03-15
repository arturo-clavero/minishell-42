/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:42:17 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 07:59:32 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
/*
char	*ft_strchr(const char *s, int c)
{
	while (*s || (*s == '\0' && c == '\0'))
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*res;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!(res))
		return (NULL);
	ft_memmove(res, s1, i);
	res[i] = '\0';
	return (res);
}

t_list	*get_last_node(t_list *list)
{
	while (list  && list->next)
		list = list->next;
	return (list);
}

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



//LIBS UP
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
	result = (char **)malloc(sizeof(char *) * n + 2);
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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_exec *ex;

	int i;
	i = -1;
	ex->env_list = NULL;
	while (env && env[++i])
		new_node((void *)env[i], &ex->env_list);
	char **result;
	result = ft_list_to_str_array(ex->env_list);
	i = -1;
	//while (result[++i])
		//printf("%s\n", result[i]);
	return (1);
}*/
*/
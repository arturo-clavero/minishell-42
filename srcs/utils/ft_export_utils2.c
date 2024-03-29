/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:02:01 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 17:12:07 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds index where variable name ends in environment node
 *
 * @param char *str - environment node->content
 * @return int - ending index of variable name
 */
int	find_end_variable_index(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] == ' ' && str[i] == '\t')
		i++;
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

/**
 * @brief Checks wether the environment variable should be substituted
 * by export argument or not
 *
 * @param char *new - export argument
 * @param char *old - environemnt node being evaluated
 * @return int - (-1) for no match, (1) for match and substitution required,
 * (0) for match and no substitution
 */

int	compare_with_equal_signs(char *new, char *old, int i)
{
	int	j;

	j = find_index_of_char(old, '=');
	if (ft_strncmp(new, old, j) == 0 && ft_strncmp(new, old, i) == 0)
	{
		if (ft_strchr(new, '='))
			return (1);
		return (0);
	}
	return (-1);
}

int	find_env_match(char *new, char *old)
{
	char	*temp_new;
	char	*temp_old;
	int		i;

	if (!new || !old)
		return (FALSE);
	temp_old = ft_strdup(old);
	i = find_index_of_char(old, '=');
	if (i > 0)
		temp_old[i] = '\0';
	temp_new = ft_strdup(new);
	i = find_index_of_char(new, '=');
	if (i > 0)
		temp_new[i] = '\0';
	if (double_strncmp(temp_old, temp_new) == 0)
	{
		free_data((void **)&temp_old, 1);
		free_data((void **)&temp_new, 1);
		if (ft_strchr(new, '='))
			return (1);
		return (0);
	}
	free_data((void **)&temp_old, 0);
	free_data((void **)&temp_new, 0);
	return (compare_with_equal_signs(new, old, i));
}

/**
 * @brief appends new value
 * @param  new str
 * @param old str
 * @return 
 */
char	*new_appended_value(char *new, char *old)
{
	int		j;
	char	*result;

	j = 0;
	while (new[j] && new[j] != '=')
		j++;
	if (ft_strchr(old, '='))
		j++;
	result = ft_strjoin(old, &new[j]);
	free_data((void **)&new, 0);
	return (result);
}

/**
 * @brief evaluates appending value to env list
 * @param new pointer to new string
 * @param env_list list of environment variables
 */
void	append_export_to_env(char **new, t_list **env_list)
{
	t_list	*node;
	int		i;

	node = *env_list;
	while (node)
	{
		i = find_env_match(*new, (char *)node->content);
		if (i == 1)
		{
			*new = new_appended_value(*new, (char *)node->content);
			delete_node(node, env_list);
			break ;
		}
		if (i == 0)
			return ;
		node = node->next;
	}
	new_node(*new, env_list);
}

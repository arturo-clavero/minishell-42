/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 06:02:01 by artclave          #+#    #+#             */
/*   Updated: 2024/03/28 03:25:20 by artclave         ###   ########.fr       */
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

int	find_index_of_char(char *str, char c)
{
	int	i;

	if (!str || str[0] == 0)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
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
int	find_env_match(char *new, char *old)
{
	char	*temp_new;
	char	*temp_old;
	int		i;

	temp_old = ft_strdup(old);
	i = find_index_of_char(old, '=');
	if (i > 0)
		temp_old[i] = '\0';
	temp_new = ft_strdup(new);
	i = find_index_of_char(new, '=');
	//printf("equal sign at[%d]\n", i);
	if (i > 0)
		temp_new[i] = '\0';
	//printf("temp_new: %s, temp_old: %s\n", temp_new, temp_old);
	if (double_strncmp(temp_old, temp_new) == 0)
	{
		//printf("match no equal sign\n");
		//if (i > 0)
		//	temp_new[i] = '=';
		if (ft_strchr(new, '='))
		{
			//printf("new has = -> %s\n", new);
			free_data(NULL, (void *)temp_old, 1);
			free_data(NULL, (void *)temp_new, 1);
			//printf("returning 1\n");
			return (1);
		}
		//printf("new has no = -> %s\n", new);
		free_data(NULL, (void *)temp_old, 0);
		return (free_data(NULL, (void *)temp_new, 0));
					

	}
//	if (i > 0)
//			temp_new[i] = '=';
	free_data(NULL, (void *)temp_old, 0);
	free_data(NULL, (void *)temp_new, 0);
//	printf("new: %s, old: %s, comparing: %d\n", new, old, i);
	if (ft_strncmp(new, old, i) == 0)
	{
		//printf("match with equal sign\n");
		if (ft_strchr(new, '='))
			return (1);
		return (0);
	}
	return (-1);
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
	free_data(NULL, (void *)new, 0);
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

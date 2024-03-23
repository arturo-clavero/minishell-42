/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:51 by artclave          #+#    #+#             */
/*   Updated: 2024/03/23 07:27:35 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Execute the env command.
 *
 * @param t_exec *ex - The execution structure
 * @return int - The exit status
 */
int	exec_env(t_exec *ex)
{
	t_list	*env_node;
	char	*found;
	char	*env_str;
	int		i;

	env_node = ex->env_list;
	while (env_node)
	{
		env_str = ((char *)env_node->content);
		found = ft_strchr(env_str, '=');
		if (found)
		{
			i = -1;
			while (env_str[++i])
			{
				if (env_str[i] != '"')
					write(STDOUT_FILENO, &env_str[i], 1);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		env_node = env_node->next;
	}
	return (0);
}

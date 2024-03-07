/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:10:51 by artclave          #+#    #+#             */
/*   Updated: 2024/03/05 11:20:44 by ugolin-olle      ###   ########.fr       */
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

	env_node = ex->env_list;
	while (env_node)
	{
		env_str = ((char *)env_node->content);
		found = ft_strchr(env_str, '=');
		if (found)
		{
			write(STDOUT_FILENO, env_str, ft_strlen(env_str));
			write(STDOUT_FILENO, "\n", 1);
		}
		env_node = env_node->next;
	}
	return (0);
}

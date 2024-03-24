/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:42:18 by artclave          #+#    #+#             */
/*   Updated: 2024/03/24 14:52:40 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Change the SHLVL.
 *
 * @param int change - The change
 * @param t_exec *ex - The execution
 * @return int
*/
int	change_shlvl(int change, t_exec *ex)
{
	char	*shlvl_str;
	int		shlvl_num;
	int		i;
	t_list	*env;

	shlvl_str = get_env_value("SHLVL=", ex->env_list);
	shlvl_num = ft_atoi(shlvl_str);
	shlvl_num += change;
	shlvl_str = ft_itoa(shlvl_num);
	env = get_env_node("SHLVL=", ex);
	i = -1;
	while (shlvl_str[++i])
		((char *)env->content)[6 + i] = shlvl_str[i];
	((char *)env->content)[6 + i] = '\0';
	if (shlvl_num >= 1000)
	{
		print_error("warning: shell level (", shlvl_str, ") too high, resetting to 1");
		change_shlvl(1 - shlvl_num, ex);
	}
	if (shlvl_num < 0)
		change_shlvl(- shlvl_num, ex);
	free(shlvl_str);
	return (shlvl_num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 06:42:18 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 16:48:03 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_shlvl(char **str, int num, t_exec *ex)
{
	t_list	*env;
	int		i;
	char	*result;

	result = ft_itoa(num);
	env = get_env_node("SHLVL=", ex);
	i = -1;
	while (result[++i])
		*((char *)(env->content) + 6 + i) = result[i];
	*((char *)(env->content) + 6 + i) = '\0';
	*str = env->content;
	free_data((void **)&result, 0);
}

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

	shlvl_str = get_env_value("SHLVL=", ex->env_list);
	if (!shlvl_str)
		return (-1);
	shlvl_num = ft_atoi(shlvl_str);
	shlvl_num += change;
	update_shlvl(&shlvl_str, shlvl_num, ex);
	if (shlvl_num >= 1000)
	{
		print_error("warning: shell level (",
			&shlvl_str[6], ") too high, resetting to 1", 0);
		return (change_shlvl((1 - shlvl_num), ex));
	}
	if (shlvl_num < 0)
		change_shlvl((shlvl_num * (-1)), ex);
	return (shlvl_num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:38:06 by artclave          #+#    #+#             */
/*   Updated: 2024/03/09 21:39:10 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Convert a string to a 128 bits integer.
 *
 * @param char *str - The string to convert
 * @return __int128_t - The 128 bits integer
 */
static __int128_t	atoi_128bits(const char *str)
{
	int			i;
	int			sign;
	__int128_t	num;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num *= 10;
		num += (str[i++] - '0');
	}
	return (num * sign);
}

/**
 * @brief Check if the argument is numeric.
 *
 * @param char *str - The string to check
 * @param __int128_t num - The 128 bits integer
 * @return int - 0 if the argument is numeric, 255 otherwise
 */

static int	check_numeric_argument(char *str, __int128_t num)
{
	int	i;

	i = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
	{
		if (num > LLONG_MAX || num < LLONG_MIN
			|| str_is_numerical(&str[i]) == FALSE)
		{
			print_error("exit: ", str, ": numeric argument required");
			return (255);
		}
	}
	return (0);
}

/**
 * @brief Get the new exit number.
 *
 * @param char *cmd - The command
 * @return int - The new exit number
 */
static int	get_new_exit_num(char *cmd)
{
	__int128_t	num;
	int			i;

	i = 0;
	skip_whitespace(cmd, &i);
	num = atoi_128bits(cmd);
	if (check_numeric_argument(&cmd[i], num) == 255)
		return (-1);
	if (num > 255 || num < 0)
		return ((int)(num % 256));
	return ((int)num);
}

/**
 * @brief Execute the exit command.
 *
 * @param char **cmd_array - The command array
 * @param t_cmd *cmd - The command structure
 * @return int - The exit status
 */
int	exec_exit(char **cmd_array, t_cmd *cmd)
{
	int		new_exit_num;
	t_redir	*redir;

	redir = cmd->redir;
	if (!redir || redir->type != PIPE)
		ft_putstr_fd("exit\n", 1);
	if (cmd_array[1] == NULL)
		exit(0);
	new_exit_num = get_new_exit_num(cmd_array[1]);
	if (new_exit_num == -1)
		return (255);
	if ((cmd_array[2]))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (new_exit_num);
}

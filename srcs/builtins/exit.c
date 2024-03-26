/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:38:06 by artclave          #+#    #+#             */
/*   Updated: 2024/03/26 05:58:38 by artclave         ###   ########.fr       */
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

static int	check_numeric_argument(char *str, __int128_t num, t_exec *ex)
{
	int	i;
	int	flag;

	flag = FALSE;
	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == TRUE)
			flag = TRUE;
		if (str[i] == '-' && str[i + 1] == 0 && i > 0 && str[i - 1] == '-')
			exit_minishell(ex, 0);
		if ((num > LLONG_MAX || num < LLONG_MIN) || (ft_isdigit(str[i]) == FALSE
			&& str[i] != '\'' && str[i] != '"' && str[i] != ' ' && str[i] != '\t')
			|| (i != 0 && (str[i - 1] == '+' || str[i -1] == '-')
			&& ft_isdigit(str[i]) == FALSE))
		{
			print_error("exit: ", str, ": numeric argument required");
			exit_minishell(ex, 2);
		}
		i++;
	}
	if (flag == FALSE)
	{
		print_error("exit: ", str, ": numeric argument required");
		exit_minishell(ex, 2);
	}
	return (0);
}

/**
 * @brief Get the new exit number.
 *
 * @param char *cmd - The command
 * @return int - The new exit number
 */
static int	get_new_exit_num(char *cmd, t_exec *ex)
{
	__int128_t	num;
	int			i;

	i = 0;
	skip_whitespace(cmd, &i);
	num = atoi_128bits(cmd);
	check_numeric_argument(&cmd[i], num, ex);
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
int	exec_exit(char **cmd_array, t_cmd *cmd, t_exec *ex)
{
	int		new_exit_num;
	t_redir	*redir;
	int		i;

	redir = cmd->redir;
	if (!redir || redir->type != PIPE)
		ft_putstr_fd("exit\n", 1);
	if (cmd_array[1] == NULL)
		return (ex->exit);
	new_exit_num = get_new_exit_num(cmd_array[1], ex);
	if ((cmd_array[2]))
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		i = 1;
		while (cmd_array[++i])
		{
			if (str_is_numerical(cmd_array[i]) == FALSE)
				return (1);
		}
		return (127);
	}
	return (new_exit_num);
}

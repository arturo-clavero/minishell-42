/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:04:37 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 16:35:12 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static __int128_t	atoi_128bits(const char *str)
{
	int			i;
	int			sign;
	__int128_t	num;

	i = 0;
	num = 0;
	sign = 1;
	if (!str)
		return (0);
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

int	is_numeric_error(__int128_t num, char *str, int i)
{
	if ((num > LLONG_MAX || num < LLONG_MIN) || (ft_isdigit(str[i]) == FALSE
			&& str[i] != '\'' && str[i] != '"' && str[i] != ' '
			&& str[i] != '\t') || (i != 0 && (str[i - 1] == '+'
				|| str[i -1] == '-') && ft_isdigit(str[i]) == FALSE))
		return (TRUE);
	return (FALSE);
}

int	non_numeric_arg(char *str)
{
	int			i;
	int			flag;
	__int128_t	num;

	flag = TRUE;
	i = 0;
	num = atoi_128bits(str);
	skip_whitespace(str, &i);
	if (str[i] == '\'' || str[i] == '"')
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i + 1])
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == TRUE)
			flag = FALSE;
		if (str[i] == '-' && str[i + 1] == 0 && i > 0 && str[i - 1] == '-')
			return (0);
		if (is_numeric_error(num, str, i) == TRUE)
			return (TRUE);
		i++;
	}
	return (flag);
}

void	print_exit(t_exec *ex)
{
	dup2(ex->stdin_original, STDIN_FILENO);
	close(ex->stdin_original);
	dup2(ex->stdout_original, STDOUT_FILENO);
	close(ex->stdout_original);
	printf("exit\n");
}

/*
* @param char **cmd_array - The command array
* @param t_cmd *cmd - The command structure
* @return int - The exit status
*/
int	exec_exit(char **cmd, t_exec *ex)
{
	__int128_t	exit_code;

	exit_code = 0;
	if (!(ex->total_pipes > 0))
		print_exit(ex);
	exit_code = atoi_128bits(cmd[1]);
	if (!cmd[1])
		exit_code = g_exit_status;
	else if (non_numeric_arg(cmd[1]) == TRUE)
	{
		print_error("exit: ", cmd[1], ": numeric argument required", 0);
		exit_code = 2;
	}
	else if (cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_code = 127;
		if (str_is_numerical(cmd[1]) == TRUE)
			exit_code = 1;
	}
	if (ex->total_pipes > 0 || (cmd[0] && cmd[1] && cmd[2]))
		return (exit_code);
	return (exit_minishell(ex, exit_code));
}

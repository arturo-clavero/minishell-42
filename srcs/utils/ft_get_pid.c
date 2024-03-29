/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:18 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 00:24:15 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief extracts the parent process id from the output of "ps" command
 * 
 * @param char *str - output of "ps" command
 * @param int i - length of "ps" command output (str)
 * @return char * - parent process id numbers as a string
 */
static char	*find_last_minishell_pid(char *str, int i)
{
	int		j;
	char	*result;

	while (i >= 0 && ft_strncmp(&str[i], "minishell",
			ft_strlen("minishell")) != 0)
		i--;
	if (i < 0)
	{
		free_data((void **)&str, 0);
		return (NULL);
	}
	while (i > 0 && str[i] != '\n')
		i--;
	while (!ft_isdigit(str[i]))
		i++;
	j = i;
	while (str[j] != ' ')
		j++;
	str[j] = '\0';
	result = ft_strdup(&str[i]);
	free_data((void **)&str, 0);
	return (result);
}

/**
 * @brief gets current parent process id
 * 
 * @param void
 * @return char * - parent process id numbers as a string
 */
char	*ft_get_pid(void)
{
	int		id;
	int		fd[2];
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * 2000);
	if (!buffer)
		return (NULL);
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[STDIN_FILENO]);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDOUT_FILENO]);
		execve("/usr/bin/ps", ft_split("ps\0", ' '), NULL);
	}
	close(fd[STDOUT_FILENO]);
	bytes = read(fd[STDIN_FILENO], buffer, 2000);
	close(fd[STDIN_FILENO]);
	buffer[bytes] = '\0';
	return (find_last_minishell_pid(buffer, bytes));
}

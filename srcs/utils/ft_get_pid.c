/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:48:18 by artclave          #+#    #+#             */
/*   Updated: 2024/03/13 23:02:39 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_last_minishell_pid(char *str, int i)
{
	int		j;
	char	*result;

	while (i >= 0 && ft_strncmp(&str[i], "minishell",
			ft_strlen("minishell")) != 0)
		i--;
	if (i < 0)
	{
		free(str);
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
	free(str);
	return (result);
}

char	*ft_get_pid(void)
{
	int		id;
	int		fd[2];
	char	*buffer;
	int		bytes;

	bytes = 1;
	buffer = (char *)malloc(sizeof(char) * 2000);
	pipe(fd);
	id = fork();
	if (id == 0)
	{
		close(fd[STDIN_FILENO]);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDOUT_FILENO]);
		execve("/usr/bin/ps", ft_split("ps\0", ' '), NULL);
	}
	else
	{
		close(fd[STDOUT_FILENO]);
		bytes = read(fd[STDIN_FILENO], buffer, 2000);
		close(fd[STDIN_FILENO]);
		buffer[bytes] = '\0';
		buffer = find_last_minishell_pid(buffer, bytes);
	}
	return (buffer);
}

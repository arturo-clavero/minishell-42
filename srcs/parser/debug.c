/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:44:38 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/20 20:11:24 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calculate length of an array.
 *
 * @param char **array - The array to calculate the length.
 * @return int - The length of the array.
 */
static int	ft_array_len(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

/**
 * @brief Print the cmd and the redir structure.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
void	ft_debug_parser(t_cmd *cmd)
{
	int	i;

	printf("\n=====================================\n\n");
	printf("\nCommand:\n\n");
	while (cmd)
	{
		i = 0;
		printf("cmd->bad_substitution: %d\n", cmd->bad_substitution);
		if (cmd->array)
		{
			printf("cmd->array length: %d\n", ft_array_len(cmd->array));
			while (cmd->array[i])
			{
				printf("cmd->array[%d]: %s\n", i, cmd->array[i]);
				i++;
			}
		}
		else
			printf("cmd->array[%d]: (null)\n", i);
		// if (cmd->redir)
		// {
		// 	printf("cmd->redir:\n");
		// 	printf("  cmd->redir->type: %d\n", cmd->redir->type);
		// 	printf("  cmd->redir->file: %s\n", cmd->redir->file_name);
		// }
		// else
		// 	printf("cmd->redir: (null)\n");
		cmd = cmd->next;
	}
	printf("\n=====================================\n\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:00:47 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/21 15:01:08 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints details of a redirection.
 *
 * @param t_redir *redir - The redirection structure.
 * @return void
 */
void	ft_print_redir(t_redir *redir)
{
	printf("Redirection:\n");
	printf("  - Type: ");
	switch (redir->type)
	{
	case PIPE:
		printf("PIPE\n");
		break ;
	case INFILE:
		printf("INFILE\n");
		break ;
	case OUTFILE:
		printf("OUTFILE\n");
		break ;
	case APPEND:
		printf("APPEND\n");
		break ;
	case HEREDOC:
		printf("HEREDOC\n");
		break ;
	default:
		printf("UNKNOWN\n");
	}
	if (redir->file_name)
		printf("  - File name: %s\n", redir->file_name);
	if (redir->heredoc_buff)
		printf("  - Heredoc buffer: %s\n", redir->heredoc_buff);
	if (redir->duplication != UNINITIALIZED)
		printf("  - Duplication: %d\n", redir->duplication);
}

/**
 * @brief Prints details of parsed commands and their redirections.
 *
 * @param t_cmd *cmd - The head of the command list.
 * @return void
 */
void	ft_debug_parser(t_cmd *cmd)
{
	while (cmd)
	{
		printf("-----\n");
		printf("Command:\n");
		printf("  - Bad substitution: %d\n", cmd->bad_substitution);
		if (cmd->array)
		{
			int i = 0;
			while (cmd->array[i])
			{
				printf("    - Argument %d: %s\n", i + 1, cmd->array[i]);
				i++;
			}
		}
		else
			printf("  - Arguments: (null)\n");
		if (cmd->redir)
		{
			t_redir *tmp_redir = cmd->redir;
			while (tmp_redir)
			{
				ft_print_redir(tmp_redir);
				tmp_redir = tmp_redir->next;
			}
		}
		else
			printf("  - Redirections: (none)\n");
		cmd = cmd->next;
	}
	printf("-----\n");
}

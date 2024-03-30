/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:12:45 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 15:56:25 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//do I need ot include global here?

/**
 * @brief Exit the minishell and free structure.
 *
 * @param t_exec *ex - The execution
 * @param int exit_num - The exit number
 * @return void
 */
int	exit_minishell(t_exec *ex, int exit_num)
{
	clean_t_cmd(ex->cmd, ex);
	clean_list(ex->env_list, FALSE);
	clean_list(ex->short_term_data, TRUE);
	clean_list(ex->long_term_data, TRUE);
	g_exit_status = exit_num;
	exit(exit_num);
	return (0);
}

/**
 * @brief Maybe quit the program.
 *
 * @param t_exec *ex - The execution
 * @return void
 */
void	maybe_quit_program(t_exec *ex)
{
	if (ex->cmd->next || !(ex->cmd->array))
		return ;
	if (ft_strncmp(ex->cmd->array[0], "exit", ft_strlen("exit")) != 0)
		return ;
	if (!(ex->cmd->array[1] == NULL
			|| !str_is_numerical(ex->cmd->array[1])
			|| (str_is_numerical(ex->cmd->array[1])
				&& ex->cmd->array[2] == NULL)))
		return ;
	exit_minishell(ex, g_exit_status);
}

/**
 * @brief Clean the list.
 *
 * @param t_list *list - The list
 * @param int clean_content - The clean content
 * @return void
 */
void	clean_list(t_list *list, int clean_content)
{
	t_list	*temp;

	if (clean_content == FALSE || list == NULL)
		return ;
	while (list && list->content)
	{
		temp = list->next;
		if (clean_content == TRUE)
			free_data((void **)&list->content, 0);
		free_data((void **)&list, 0);
		list = NULL;
		list = temp;
	}
}

void	clean_redir(t_redir	*redir)
{
	t_redir	*temp_redir;

	while (redir)
	{
		temp_redir = redir->next;
		free_data((void **)&(redir->file_name), 0);
		free_data((void **)&(redir->heredoc_buff), 0);
		free_data((void **)&redir, 0);
		redir = temp_redir;
	}
}

/**
 * @brief Clean the t_cmd structure.
 *
 * @param t_cmd *cmd - The command structure
 * @return void
 */
void	clean_t_cmd(t_cmd *cmd, t_exec *ex)
{
	int		i;
	t_cmd	*temp_cmd;

	while (cmd)
	{
		i = -1;
		clean_redir(cmd->redir);
		if (cmd->array)
		{
			while (cmd->array[++i])
				free_data((void **)&(cmd->array[i]), 0);
			free_data((void **)&(cmd->array), 0);
		}
		temp_cmd = cmd->next;
		free_data((void **)&cmd, 0);
		cmd = temp_cmd;
	}
	ex->cmd = NULL;
}

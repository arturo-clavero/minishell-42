/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:12:45 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 03:29:49 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exit the minishell and free structure.
 *
 * @param t_exec *ex - The execution
 * @param int exit_num - The exit number
 * @return void
 */
void	exit_minishell(t_exec *ex, int exit_num)
{
	clean_t_cmd(ex->cmd);
	clean_list(ex->env_list, FALSE);
	clean_list(ex->short_term_data, TRUE);
	clean_list(ex->long_term_data, TRUE);
	exit(exit_num);
}

/**
 * @brief Maybe quit the program.
 *
 * @param t_exec *ex - The execution
 * @return void
 */
void	maybe_quit_program(t_exec *ex)
{
	if (ex->cmd->next)
		return ;
	if (ft_strncmp(ex->cmd->array[0], "exit", ft_strlen("exit")) != 0)
		return ;
	if (!(ex->cmd->array[1] == NULL
			|| !str_is_numerical(ex->cmd->array[1])
			|| (str_is_numerical(ex->cmd->array[1])
				&& ex->cmd->array[2] == NULL)))
		return ;
	exit_minishell(ex, ex->exit);
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
			free(list->content);
		free(list);
		list = temp;
	}
}

/**
 * @brief Clean the t_cmd structure.
 *
 * @param t_cmd *cmd - The command structure
 * @return void
 */
void	clean_t_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*temp_cmd;
	t_redir	*temp_redir;

	while (cmd)
	{
		i = -1;
		while (cmd->redir)
		{
			temp_redir = cmd->redir->next;
			free(cmd->redir);
			cmd->redir = temp_redir;
		}
		while (cmd->array[++i])
			free(cmd->array[i]);
		free(cmd->array);
		temp_cmd = cmd->next;
		free(cmd);
		cmd = temp_cmd;
	}
}

/**
 * @brief Add data to the cleanup list.
 *
 * @param void *content - The content
 * @param t_list **list - The list
 * @return void
 */
void	add_data_to_cleanup_list(void *content, t_list **list)
{
	t_list	*node;

	node = NULL;
	if (!content)
		return ;
	new_node(content, &node);
	node->next = (*list);
	(*list) = node;
}

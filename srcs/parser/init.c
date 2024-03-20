/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 00:55:23 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/20 19:55:33 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize the command and redirection structure.
 *
 * @param t_exec *ex - The minishell object.
 * @return void
 */
t_cmd	*ft_init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->array = NULL;
	new_cmd->redir = NULL;
	new_cmd->bad_substitution = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

/**
 * @brief Initialize the redirection structure.
 *
 * @param void
 * @return t_redir* The new redirection.
 */
t_redir	*ft_init_redir(void)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->file_name = NULL;
	new_redir->heredoc_buff = NULL;
	new_redir->type = UNINITIALIZED;
	new_redir->duplication = UNINITIALIZED;
	new_redir->next = NULL;
	return (new_redir);
}

/**
 * @brief Add a new redirection.
 *
 * @param t_redir *redir - The redirection to add.
 * @param char *file_name - The file name to add to the redirection.
 * @param char *heredoc_buff - The heredoc buffer to add to the redirection.
 * @param int type - The redirection type to add to the redirection.
 * @param int - 1 if success, 0 if error.
 */
int	ft_add_redir(t_redir *redir, char *file_name, char *heredoc_buff, int type)
{
	t_redir	*tmp;
	t_redir	*node;

	node = ft_init_redir();
	if (!node)
		return (0);
	node->file_name = file_name;
	node->heredoc_buff = heredoc_buff;
	node->type = type;
	node->duplication = STDOUT_FILENO;
	tmp = redir;
	if (tmp == NULL)
	{
		redir = node;
		return (1);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

/**
 * @brief Add new command to the structure.
 *
 * @param t_cmd **cmd - The command to add.
 * @param char *array - The array to add to the command.
 * @param t_redir *redir - The redirection to add to the command.
 * @param int count_token - The number of token to add to the command.
 * @return int - 1 if success, 0 if error.
 */
int	ft_add_cmd(t_cmd **cmd, char **array, t_redir *redir, int count_token)
{
	t_cmd	*tmp;
	t_cmd	*node;

	node = ft_init_cmd();
	if (!node)
		return (0);
	node->array = malloc(sizeof(char *) * (count_token + 1));
	if (!node->array)
		return (0);
	ft_memcpy(node->array, array, sizeof(char *) * (count_token + 1));
	(void)redir;
	node->next = NULL;
	if (*cmd == NULL)
	{
		*cmd = node;
		return (1);
	}
	tmp = *cmd;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	return (1);
}

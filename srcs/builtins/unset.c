/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:32:23 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 15:40:25 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check the syntax of the unset command.
 *
 * @param char **array - The command array
 * @return int - EXIT_SUCCESS if the syntax is correct, EXIT_FAILURE otherwise
 */
static int	check_unset_syntax(char **array)
{
	int	i;
	int	j;

	i = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			if (ft_isdigit(array[i][0]) || (!ft_isdigit(array[i][j])
					&& !ft_isalpha(array[i][j]) && array[i][j] != '_'))
				return (1);
		}
	}
	return (0);
}

/**
 * @brief Delete a node from the list.
 *
 * @param t_list *node_delete - The node to delete
 * @param t_list **head - The head of the list
 * @return void
 */
void	delete_node(t_list *node_delete, t_list **head)
{
	t_list	*list;

	if (node_delete == NULL)
		return ;
	list = *head;
	if (list == node_delete)
	{
		list = node_delete->next;
		free_data((void **)&node_delete, 0);
		return ;
	}
	while (list)
	{
		if (list->next == node_delete)
		{
			list->next = list->next->next;
			free_data((void **)&node_delete, 0);
			return ;
		}
		list = list->next;
	}
}

/**
 * @brief Execute the unset command.
 *
 * @param char **cmd_array - The command array
 * @param t_exec *ex - The execution structure
 * @return int - The exit status
 */
int	exec_unset(char **cmd, t_exec *ex)
{
	int		i;
	t_list	*node;

	if (ex->cmd->next)
		return (0);
	if (check_unset_syntax(cmd) == EXIT_FAILURE)
		return (1);
	i = 0;
	while (cmd && cmd[0] && cmd[++i])
	{
		node = ex->env_list;
		while (node)
		{
			if (find_env_match(cmd[i], (char *)node->content) != -1)
			{
				delete_node(node, &ex->env_list);
				break ;
			}
			node = node->next;
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:56 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 15:40:39 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the export syntax is valid
 *
 * @param char **cmd_array - The command array
 * @param char *original_cmd - The original command
 * @return int - 0 if the syntax is valid, 1 otherwise
 */
static int	is_export_syntax_valid(char **cmd_array, int *add_flag)
{
	char	*original;
	int		error;

	original = ft_strdup(*cmd_array);
	error = is_variable_start_valid(*cmd_array, original);
	if (error > 0)
		return (free_data((void **)&original, error));
	error = is_variable_content_valid(cmd_array, original, add_flag);
	if (error > 0)
		return (free_data((void **)&original, error));
	add_slash_to_inside_double_quotes(cmd_array, ft_strlen(*cmd_array));
	return (free_data((void **)&original, 0));
}

/**
 * @brief Adds export argument to enviroment list
 *
 * @param char *export_str - export argument -> variable="value"
 * @param t_list **env_list - pointer to environment list
 * @return void
 */
void	add_export_to_env(char *export_str, t_exec *ex)
{
	t_list	*node;
	int		i;

	i = -1;
	node = ex->env_list;
	while (node)
	{
		i = find_env_match(export_str, (char *)node->content);
		if (i == 1)
		{
			delete_node(node, &ex->env_list);
			break ;
		}
		else if (i == 0)
			return ;
		node = node->next;
	}
	new_node((void *)export_str, &ex->env_list);
}

void	export_each_argument(char **str, int *error, t_exec *ex)
{
	int		add_flag;
	char	*new_value;

	add_flag = FALSE;
	new_value = NULL;
	if (is_export_syntax_valid(str, &add_flag) > 0)
	{
		*error = 1;
		return ;
	}
	new_value = ft_strdup(*str);
	if (add_flag == TRUE)
		append_export_to_env(&new_value, &ex->env_list);
	else
		add_export_to_env(new_value, ex);
	add_data_to_cleanup_list(new_value, &ex->long_term_data);
}

/**
 * @brief Execute the export command.
 *
 * @param char **cmd_array - The command array
 * @param t_exec *ex - The execution structure
 * @return int - 0 if the command is executed successfully, 1 otherwise
 */
int	exec_export(char **cmd_array, t_exec *ex)
{
	int		i;
	int		error;

	error = 0;
	if (ex->cmd->next && cmd_array[1])
		return (0);
	i = 0;
	while (cmd_array[++i])
		export_each_argument(&cmd_array[i], &error, ex);
	if (!cmd_array[1])
		print_env_alphabetically(ex->env_list, ex->env_list);
	return (error);
}

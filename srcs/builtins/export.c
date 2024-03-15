/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:56 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 19:16:50 by artclave         ###   ########.fr       */
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
static int	is_export_syntax_valid(char **cmd_array, char *original_cmd)
{
	int	error;

	error = has_unclosed_quotes(*cmd_array, original_cmd);
	if (error > 0)
		return (error);
	delete_outside_quotes(cmd_array);
	error = is_variable_start_valid(*cmd_array, original_cmd);
	if (error > 0)
		return (error);
	error = is_variable_content_valid(*cmd_array, original_cmd);
	if (error > 0)
		return (error);
	add_slash_to_inside_double_quotes(cmd_array, ft_strlen(*cmd_array));
	if (ft_strchr(*cmd_array, '='))
		add_quotes_around_value(cmd_array);
	return (0);
}

/**
 * @brief Finds index where variable name ends in environment node
 *
 * @param char *str - environment node->content
 * @return int - ending index of variable name
 */
int	find_end_variable_index(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] == ' ' && str[i] == '\t')
		i++;
	while (str[i] && str[i] != '=' && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

/**
 * @brief Checks wether the environment variable should be substituted
 * by export argument or not
 *
 * @param char *new - export argument
 * @param char *old - environemnt node being evaluated
 * @return int - (-1) for no match, (1) for match and substitution required,
 * (0) for match and no substitution
 */
int	find_env_match(char *new, char *old)
{
	int	len;

	len = find_end_variable_index(new);
	if (find_end_variable_index(old) != len)
		return (-1);
	if (ft_strncmp(new, old, len) != 0)
		return (-1);
	if (ft_strchr(new, '='))
		return (1);
	return (0);
}

/**
 * @brief Adds export argument to enviroment list
 *
 * @param char *export_str - export argument -> variable="value"
 * @param t_list **env_list - pointer to environment list
 * @return void
 */
void	add_export_to_env(char *export_str, t_list **env_list)
{
	t_list	*node;
	int		i;

	node = *env_list;
	while (node)
	{
		i = find_env_match(export_str, (char *)node->content);
		if (i == 1)
		{
			delete_node(node, env_list);
			break ;
		}
		if (i == 0)
			return ;
		node = node->next;
	}
	new_node(export_str, env_list);
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
	char	*original_cmd_str;
	char	*new_value;
	int		error;

	new_value = NULL;
	original_cmd_str = NULL;
	if (has_pipe(ex->cmd) == TRUE && cmd_array[1])
		return (0);
	i = 0;
	while (cmd_array[++i])
	{
		original_cmd_str = ft_strdup(cmd_array[i]);
		error = is_export_syntax_valid(&cmd_array[i], original_cmd_str);
		if (error > 0)
			return (error);
		new_value = ft_strdup(cmd_array[i]);
		add_export_to_env(new_value, &ex->env_list);
		add_data_to_cleanup_list(new_value, &ex->long_term_data);
		free(original_cmd_str);
	}
	if (!cmd_array[1])
		print_env_alphabetically(ex->env_list, ex->env_list);
	return (0);
}

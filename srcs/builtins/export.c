/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:56 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 05:38:08 by artclave         ###   ########.fr       */
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


t_list	*env_variable_exists(char *str, t_list *env, int double_check)
{
	char *temp;
	int	len;

	if (!double_check)
	{
		temp = ft_strchr(str, '=');
		if (temp == NULL)
			return (NULL);
		len = ft_strlen(str) - ft_strlen(temp) + 1;
	}
	if (double_check)
		len = ft_strlen((char *)env->content);
	while (env)
	{
		if (ft_strncmp(str, (char *)env->content, len) == 0)
				return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_export_to_env(char *export_str, t_list **env_list)
{
	char	*variable;
	int		i;
	t_list	*old_node;

	old_node = NULL;
	variable = ft_strdup(export_str);
	i = 0;	
	while (variable[i] && variable[i] != '=' && variable[i] != ' '
		&& variable[i] != '\t')
		i++;
	variable[i] = '\0';
	old_node = env_variable_exists(variable, *env_list, 1);
	if (!old_node)
		old_node = env_variable_exists(export_str, *env_list, 0);
	if (old_node)
		old_node->content = export_str;
	else
			new_node(export_str, env_list);
	free(variable);
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
	}
	if (!cmd_array[1])
		print_env_alphabetically(ex->env_list, ex->env_list);
	else
		free(original_cmd_str);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:56 by artclave          #+#    #+#             */
/*   Updated: 2024/03/27 01:13:55 by artclave         ###   ########.fr       */
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
		return (error);
	error = is_variable_content_valid(cmd_array, original, add_flag);
	if (error > 0)
		return (error);
	add_slash_to_inside_double_quotes(cmd_array, ft_strlen(*cmd_array));
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
int	find_env_match(char *str, char *old)
{
	int		i;
	char	*new;
	char	*result;

	i = 0;
	new = ft_strdup(str);
	while(new[i] && new[i] != '=')
		i++;
	new[i] = '\0';
	if (double_strncmp(new, old) == 0)
	{
		free(new);
		return (1);
	}
	result = ft_strjoin(new, "=\0");
	if (ft_strncmp(result, old, ft_strlen(result)) == 0)
	{
		free(new);
		free(result);
		if(ft_strchr(str, '='))
		{
			return (1);
		}
		return (0);
	}
	free(result);
	free(new);
	return (-1);
}

char	*new_appended_value(char *new, char *old)
{
	int	j;
	char *result;

	j = 0;
	while (new[j] && new[j] != '=')
		j++;
	if (ft_strchr(old, '='))
		j++;
	//printf("joining [%s] [%s]\n", old, &new[j]);
	result = ft_strjoin(old, &new[j]);
	free(new);
	return (result);
}

void	append_export_to_env(char **new, t_list **env_list)
{
	t_list	*node;
	int		i;

	node = *env_list;
	while (node)
	{
		i = find_env_match(*new, (char *)node->content);
		if (i == 1)
		{
			*new = new_appended_value(*new, (char *)node->content);
			delete_node(node, env_list);
			break ;
		}
		if (i == 0)
			return ;
		node = node->next;
	}
	new_node(*new, env_list);
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

	node = ex->env_list;
	while (node)
	{
		i = find_env_match(export_str, (char *)node->content);
		if (i == 1)
		{
			delete_node(node, &ex->env_list);
			break ;
		}
		if (i == 0)
			return ;
		node = node->next;
	}
	new_node((void *)export_str, &ex->env_list);
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
	char	*new_value;
	int		add_flag;
	int		error;

	new_value = NULL;
	error = 0;
	if (has_pipe(ex->cmd) == TRUE && cmd_array[1])
		return (0);
	i = 0;
	while (cmd_array[++i])
	{
		add_flag = FALSE;
		if (is_export_syntax_valid(&cmd_array[i], &add_flag) > 0)
		{
			error = 1;
			continue ;
		}
		new_value = ft_strdup(cmd_array[i]);
		if (add_flag == TRUE)
			append_export_to_env(&new_value, &ex->env_list);
		else
			add_export_to_env(new_value, ex);
		add_data_to_cleanup_list(new_value, &ex->long_term_data);
	}
	if (!cmd_array[1])
		print_env_alphabetically(ex->env_list, ex->env_list);
	return (error);
}

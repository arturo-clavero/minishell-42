/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:33:24 by artclave          #+#    #+#             */
/*   Updated: 2024/03/22 15:23:48 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief	manipulates string based on curly brackets syntax 
 * 
 * @param char **str - pointer to string being manipulated
 * @param int j - index of first char right after '$'
 * @return int - (-1) for curly bracket syntax error, (0) for no error
 */
static int	check_curly_brackets(char **str, int j)
{
	int	i;

	i = j;
	if ((*str)[i] != '{')
		return (0);
	while ((*str)[i] && (*str)[i] != '}')
		i++;
	if ((*str)[i] == '\0')
		return (-1);
	if ((*str)[j + 1] == '?')
		return (trim_question_mark(str, j));
	i = j;
	while ((*str)[++i] && (*str)[i] != '}')
	{
		if (!ft_isdigit((*str)[i]) && !ft_isalpha((*str)[i])
			&& (*str)[i] != '_')
			return (-1);
	}
	trim_curly_brackets_only(str, j);
	return (0);
}

/**
 * @brief Gets expandable variables from enviroment list
 * 
 * @param char *str - string being expanded
 * @param int i - index of first char right after '$'
 * @param int *j - int pointer that will be modified to indicate
 * the ending index of the new expanded value
 * @return char * - modified string with expanded value
 */
char	*get_expandable_value(char *str, int i, int *j, t_exec *ex)
{
	char	*temp;
	char	*result;
	int		end;

	(*j)--;
	while (str[*j] && (ft_isdigit(str[*j]) || ft_isalpha(str[*j])
			|| str[*j] == '_'))
		(*j)++;
	temp = ft_strjoin(&(str)[i], "=\0");
	result = get_env_value(temp, ex->env_list);
	if (result == NULL)
		return (result);
	end = ft_strlen(result) -1;
	if (result[0] == '\"' && result[end] == '\"')
	{
		result[end] = '\0';
		result = &result[1];
	}
	free(temp);
	return (result);
}

/**
 * @brief Trims curly brackets and identifies different expandable types
 * 
 * @param char **str - pointer to string to be expanded
 * @param int *i - pointer to current char in string being evaluated
 * @param t_exec *ex - exec structure
 * @return int - (-1) for expanding errors, (0) for no expanding value
 * (1) for successful expansion
 *  */
int	expand_variable(char **str, int *i, t_exec *ex)
{
	int		j;
	char	*value;
	char	*result;

	(*i)++;
	j = *i + 1;
	value = NULL;
	if (check_curly_brackets(str, *i) == -1)
		return (-1);
	if ((*str)[*i] == '?')
		value = ft_itoa(ex->exit);
	else if ((*str)[*i] == '$')
		value = ft_get_pid();
	else
		value = ft_strdup(get_expandable_value(*str, *i, &j, ex));
	if (value == NULL)
		return (trim_dollar_substr(str));
	(*str)[*i - 1] = '\0';
	*i = ft_strlen(*str) + ft_strlen(value);
	result = ft_join_3_strings(*str, value, &(*str)[j]);
	if (value)
		free(value);
	free(*str);
	*str = result;
	return (1);
}

/**
 * @brief Checks strings for '$' and sends them to be expanded depending
 * on quote status (if within double or/and single quotes) 
 * 
 * @param t_cmd **cmd - pointer to current command node
 * @param t_exec *ex - exec structure
 * @param char *str - string to be evaluated for '$'
 * @return char * - expanded string
 */
char	*check_str_expandables(t_cmd **cmd, t_exec *ex, char *str)
{
	int		i;
	int		double_quotes;
	int		single_quotes;

	i = -1;
	(void)cmd;
	(void)ex;
	double_quotes = FALSE;
	single_quotes = FALSE;
	while (++i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '"')
			double_quotes ^= 1;
		if (str[i] == '\'')
			single_quotes ^= 1;
		if (str[i] == '$' && (double_quotes
				|| (!double_quotes && !single_quotes)))
		{
			if (expand_variable(&str, &i, ex) == -1)
				(*cmd)->bad_substitution = TRUE;
		}
	}
	return (str);
}

/**
 * @brief Iterates through each command node and redir node and sends
 * all strings to be checked for expandables
 * 
 * @param t_cmd **cmd_head - pointer to head of command list
 * @param t_exec *ex = exec structure
 * @return void
 */

void	expand_each_cmd_node(t_cmd **cmd_head, t_exec *ex)
{
	int		i;
	t_cmd	*cmd;
	t_redir	*redir;
	char	*file;

	cmd = *cmd_head;
	while (cmd)
	{
		(cmd)->bad_substitution = FALSE;
		i = -1;
		while ((cmd)->array[++i])
			cmd->array[i] = check_str_expandables(&cmd, ex, cmd->array[i]);
		redir = cmd->redir;
		while (redir)
		{
			file = redir->file_name;
			if (redir->type != PIPE && redir->type != HEREDOC)
				file = check_str_expandables(&cmd, ex, file);
			redir = redir->next;
		}
		(cmd) = (cmd)->next;
	}
}

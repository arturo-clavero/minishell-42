/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:33:24 by artclave          #+#    #+#             */
/*   Updated: 2024/03/26 07:22:23 by artclave         ###   ########.fr       */
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
 * USER home -> $HOME" expanded value
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
	temp = modify_str_for_expansion(&str[i]);
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
 * @param qt	- if there is a double quote
 * @return int - (-1) for expanding errors, (0) for no expanding value
 * (1) for successful expansion
 *  */
/*
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
*/

void	expand_tilde(char **str, int i, t_exec *ex)
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*result;

	if (i > 0 && (*str)[i - 1] != ' ' && (*str)[i - 1] != '\t')
		return ;
	if ((*str)[i + 1] && (*str)[i + 1] != 0 && (*str)[i + 1] != ' '
		&& (*str)[i + 1] != '\t')
		return ;
	str1 = ft_strdup(*str);
	str1[i] = '\0';
	str2 = get_env_value("HOME=", ex->env_list);
	str3 = &(*str)[i + 1];
	if (!str3 || str3[0] == 0)
		str3 = NULL;
	result = ft_join_3_strings(str1, str2, str3);
	free(*str);
	free(str1);
	*str = result;
}

int	expand_dollar(char **original, int start, t_exec *ex, int curly)
{
	int		end;
	char	*value;
	char	*result;
	char	*str;

	//getting end of expandable
	str = ft_strdup(*original);
	value = NULL;
	end = start;
	if (curly && check_curly_brackets(&str, start) == -1)
		return (-1);
	while (str[end] && (ft_isalpha(str[end]) == TRUE
		|| (ft_isalnum(str[end]) == TRUE && end > start)
		|| str[end] == '_'))
		end++;
	//return if just dollar
	if (str[start] == '$' || str[start] == '?')
		end++;
	//printf("end[%d]->{%s}\n", end, &str[end]);
	if (end - start == 0)
	{
		//printf("return\n");
		//exit(2);
		return (0);
	}
	if (str[start] == '?')//check for exit number
		value = ft_itoa(ex->exit);
	else if (str[start] == '$')//check for pid
		value = ft_get_pid();
	else
	{
		str[end] = '\0';
		value = ft_strdup(get_env_value(&str[start], ex->env_list));
		if (value)
		{
			delete_char_from_str(0, &value);
			if (ft_strchr(value, '='))
			{
				free(value);
				value = NULL;
			}
		}
	}
	//printf("value: %s\n", value);
	str[start - 1] = '\0'; //setting dollar equal to NULL first part until dollar + value + original at end
	if (value)
	{
		//printf("joining [%s] + [%s] + [%s]\n", str, value, &(*original)[end]);
		result = ft_join_3_strings(str, value, &(*original)[end]);
		free(value);
	}
	else
	{
		//printf("joining [%s] + [%s]\n", str, &(*original)[end]);
		result = ft_strjoin(str, &(*original)[end]);
	}
	free(*original);
	free(str);
	*original = result;
	//printf("str->{%s}\n\n\n", result);
	//exit(0);
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
	int		dq;
	int		sq;
	int		exp;

	i = -1;
	(void)cmd;
	(void)ex;
	dq = CLOSED;
	sq = CLOSED;
	exp = 2;
	while (++i < (int)ft_strlen(str) && str[i])
	{
		if ((str[i] == '"' && sq == OPEN) || (str[i] == '\'' && dq == OPEN))
			continue;
		else if (str[i] == '"')
			dq ^= 1;
		else if (str[i] == '\'')
			sq ^= 1;
		else if (str[i] == '$' && sq == CLOSED)
		{
			exp = expand_dollar(&str, i + 1, ex, TRUE);
			if (exp == -1)
				(*cmd)->bad_substitution = TRUE;
			if (exp == 1)
				i --;
		}
		else if (str[i] == '~' && sq == CLOSED && dq == CLOSED)
			expand_tilde(&str, i, ex);
	}
	if ((*cmd)->bad_substitution < 0)
		(*cmd)->bad_substitution = TRUE;
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
		while (cmd->array && cmd->array[++i])
			cmd->array[i] = check_str_expandables(&cmd, ex, cmd->array[i]);
		redir = cmd->redir;
		while (redir)
		{
			file = redir->file_name;
			if (file && redir->type != PIPE && redir->type != HEREDOC)
				redir->file_name = check_str_expandables(&cmd, ex, file);
		//	printf("redir->{%s}\n", redir->file_name);
			redir = redir->next;
		}
		(cmd) = (cmd)->next;
	}
}

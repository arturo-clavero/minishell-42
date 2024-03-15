/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:33:24 by artclave          #+#    #+#             */
/*   Updated: 2024/03/15 07:32:16 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	expand_each_cmd_node(t_cmd **cmd_head, t_exec *ex)
{
	int		i;
	t_cmd	*cmd;
	t_redir	*redir;

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
			if (redir->type != PIPE && redir->type != HEREDOC)
				redir->file_name = check_str_expandables(&cmd, ex, redir->file_name);
			redir = redir->next;
		}
		(cmd) = (cmd)->next;
	}
}

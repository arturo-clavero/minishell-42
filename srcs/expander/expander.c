/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:33:24 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 00:58:39 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_data((void **)&temp, 0);
	return (result);
}

/**
 * @brief expands ~
 * @param str pointer to string being expanded
 * @param i index where '~' was found
 * @param ex main structure (all data)
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
		&& (*str)[i + 1] != '\t' && (*str)[i + 1] != '/')
		return ;
	str1 = ft_strdup(*str);
	str1[i] = '\0';
	str2 = get_env_value("HOME=", ex->env_list);
	str3 = &(*str)[i + 1];
	if (!str3 || str3[0] == 0)
		str3 = NULL;
	result = ft_join_3_strings(str1, str2, str3);
	free_data((void **)str, 0);
	free_data((void **)&str1, 0);
	*str = result;
}

/**
 * @brief assign quotes values baased on wether they are open or closed
 * @param c character being evaluated for quotes
 * @param sq single quotes int with values of either OPEN or CLOSED
 * @param dq double quotes int with values of either OPEN or CLOSED
 */
void	quotes_open_or_closed(char c, int *sq, int *dq)
{
	if ((c == '"' && *sq == OPEN) || (c == '\'' && *dq == OPEN))
		return ;
	else if (c == '"')
		*dq ^= 1;
	else if (c == '\'')
		*sq ^= 1;
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
	dq = CLOSED;
	sq = CLOSED;
	while (++i < (int)ft_strlen(str) && str[i])
	{
		quotes_open_or_closed(str[i], &sq, &dq);
		if (str[i] == '$' && sq == CLOSED)
		{
			exp = expand_dollar(&str, i + 1, ex, TRUE);
			if (exp == -1)
				(*cmd)->bad_substitution = TRUE;
			if (exp > 0)
				i -= exp;
		}
		else if (str[i] == '~' && sq == CLOSED && dq == CLOSED)
			expand_tilde(&str, i, ex);
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
		while (cmd->array && cmd->array[++i])
			cmd->array[i] = check_str_expandables(&cmd, ex, cmd->array[i]);
		redir = cmd->redir;
		while (redir)
		{
			file = redir->file_name;
			if (file && redir->type != PIPE && redir->type != HEREDOC)
				redir->file_name = check_str_expandables(&cmd, ex, file);
			redir = redir->next;
		}
		(cmd) = (cmd)->next;
	}
}

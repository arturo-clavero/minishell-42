/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:59:49 by artclave          #+#    #+#             */
/*   Updated: 2024/03/30 17:02:32 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief expand dollar signs with heredoc rules
 * @param str pointer to completed heredoc content
 * @param ex main strcture (all data)
 */
void	find_dollar(char **str, t_exec *ex)
{
	int	i;

	i = 0;
	if (!ft_strchr(*str, '$'))
		return ;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	expand_dollar(str, i + 1, ex, FALSE);
}

/**
 * @brief processes user input into an expanded single string
 * @param line ptr to string from readline user input
 * @param doc ptr to string containing heredoc content
 * @param ex main structure (all data)
 */
void	process_content(char **line, char **doc, t_exec *ex)
{
	char	*temp;

	temp = NULL;
	find_dollar(line, ex);
	if (*doc == NULL)
		*doc = ft_strjoin(*line, "\n\0");
	else
	{
		temp = ft_join_3_strings(*doc, *line, "\n\0");
		free_data((void **)doc, 0);
		*doc = temp;
	}
	free_data((void **)line, 0);
}

void	heredoc_quotes(t_redir *rd, t_exec *ex)
{
	int	i;
	int	dq;
	int	sq;

	dq = CLOSED;
	sq = CLOSED;
	i = -1;
	while ((rd->heredoc_buff)[++i])
	{
		if ((rd->heredoc_buff[i] == '\'' && dq == OPEN)
			|| (rd->heredoc_buff[i] == '"'
				&& sq == OPEN))
			continue ;
		else if (rd->heredoc_buff[i] == '\'')
			trim_quote(&rd->heredoc_buff, &i, &sq);
		else if (rd->heredoc_buff[i] == '"')
			trim_quote(&(rd->heredoc_buff), &i, &dq);
	}
	if (dq == OPEN || sq == OPEN)
	{
		ft_putstr_fd(ERROR_NO_CLOSE_QUOTE, 2);
		clean_t_cmd(ex->cmd, ex);
		clean_list(ex->short_term_data, TRUE);
		ft_launch_minishell(ex);
	}
}

/**
 * @brief open heredoc and store heredoc content in redir->heredoc_buffer
 * @param redir redir node containing delimeter in heredoc_buff
 * @param ex main structure (all data)
 */
void	open_heredoc(t_redir *redir, t_exec *ex)
{
	char	*doc;
	char	*line;

	doc = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (double_strncmp(line, redir->heredoc_buff) == 0)
		{
			free_data((void **)&(redir->heredoc_buff), 0);
			redir->heredoc_buff = ft_strdup(doc);
			free_data((void **)&doc, 0);
			break ;
		}
		else
			process_content(&line, &doc, ex);
	}
	free_data((void **)&line, 0);
}

/**
 * @brief find heredoc redirections
 * @param ex main structure (all data)
 */
void	heredoc(t_exec *ex)
{
	t_redir	*redir;
	t_cmd	*cmd;

	cmd = ex->cmd;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == HEREDOC && redir->heredoc_buff)
			{
				heredoc_quotes(redir, ex);
				open_heredoc(redir, ex);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

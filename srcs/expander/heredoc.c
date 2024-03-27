/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:59:49 by artclave          #+#    #+#             */
/*   Updated: 2024/03/27 03:40:34 by artclave         ###   ########.fr       */
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
		free(*doc);
		*doc = temp;
	}
	free(*line);
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
			free(redir->heredoc_buff);
			redir->heredoc_buff = doc;
			break ;
		}
		process_content(&line, &doc, ex);
	}
	free(line);
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
				open_heredoc(redir, ex);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

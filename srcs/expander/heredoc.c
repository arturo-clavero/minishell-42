/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 06:59:49 by artclave          #+#    #+#             */
/*   Updated: 2024/03/26 22:53:56 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	open_heredoc(t_redir *redir, t_exec *ex)
{
	char	*doc;
	char	*line;
	char	*temp;

	doc = NULL;
	while (1)
	{
		temp = NULL;
		line = readline("> ");
		if (!line)
			break;
		if (double_strncmp(line, redir->heredoc_buff) == 0)
		{
			free(redir->heredoc_buff);
			redir->heredoc_buff = doc;
			break;
		}
		find_dollar(&line, ex);
		if (doc == NULL)
			doc = ft_strjoin(line, "\n\0");
		else
		{
			temp = ft_join_3_strings(doc, line, "\n\0");
			free(doc);
			doc = temp;
		}
		free(line);
	}
	free(line);
}

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
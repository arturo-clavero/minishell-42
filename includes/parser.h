/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:30 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/20 18:03:49 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// -- LIBRARIES --
# include "minishell.h"

// -- PROTOTYPES --
void	ft_debug_parser(t_cmd *cmd);
void	ft_parser_error(t_exec *ex, char *message);
t_cmd	*ft_init_cmd(void);
t_redir	*ft_init_redir(void);
int		ft_add_redir(t_redir *redir, char *file_name, char *heredoc_buff,
			int type);
int		ft_add_cmd(t_cmd **cmd, char **array, t_redir *redir, int count_token);
int		ft_close_quotes(char *str, int i, char c);
int		ft_count_token(t_lexer *lexer);
void	ft_parser(t_exec *ex);

#endif

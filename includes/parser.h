/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:30 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/28 19:42:44 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// -- LIBRARIES --
# include "minishell.h"

// -- PROTOTYPES --
void	ft_debug_parser(t_cmd *cmd);

void	ft_syntax_error(t_exec *ex, int token, int status);
void	ft_parser_clean(t_exec *ex, int err_code);
void	ft_parser_error(t_exec *ex, int status);

char	**ft_malloc_node_array(t_lexer *lexer);
void	ft_add_cmd_node_to_list(t_cmd *node, t_cmd **cmd);

t_cmd	*ft_init_cmd(void);
t_redir	*ft_init_redir(t_cmd **node);
void	ft_add_redir(t_cmd **node, t_lexer **lexer);
void	ft_add_cmd(t_cmd **cmd, t_lexer *lexer, t_exec *ex);

void	ft_check_syntax(t_exec *ex);

char	*ft_get_file_name(t_lexer *lexer);
char	*ft_get_heredoc_buff(t_lexer *lexer);

void	ft_parser(t_lexer *lexer, t_exec *ex);

void	initialize_parsing(t_exec *ex);

#endif

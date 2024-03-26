/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:34:34 by artclave          #+#    #+#             */
/*   Updated: 2024/03/26 07:21:53 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// -- LIBRAIRIES --
# include "minishell.h"

// -- PROTOTYPES --
void	expand_each_cmd_node(t_cmd **cmd, t_exec *ex);
void	check_expandables(char **str);
int		expand_variable(char **str, int *i, t_exec *ex);
int		trim_question_mark(char **str, int j);
int		trim_curly_brackets_only(char **str, int j);
int		trim_dollar_substr(char *str, char **original);
int		only_dollar_sign(char *str, int i, int double_quotes);
int		expand_dollar(char **original, int start, t_exec *ex, int curly);
char	*modify_str_for_expansion(char *input);
void	quotes(t_cmd *cmd, t_exec *ex);
void	heredoc(t_exec *ex);

#endif
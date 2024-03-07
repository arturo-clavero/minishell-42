/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:44:31 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 11:14:26 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_EXEC_H
# define UTILS_EXEC_H

// -- LIBRARIES --
# include "minishell.h"

// -- PROTOTYPES --
void	new_node(void *content, t_list **list);
t_list	*get_last_node(t_list *list);
char	*get_env_value(char *variable, t_list *env_list);
t_list	*get_env_node(char *variable, t_exec *ex);
int		free_data(char *should_exit, char *data, int exit_code);
void	print_error(char *str1, char *str2, char *str3);
int		malloc_error(void);
int		is_letter(char c);
void	skip_whitespace(char *str, int *i);
int		str_is_numerical(char *str);
int		has_pipe(t_cmd *cmd);

#endif

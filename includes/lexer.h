/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:37:19 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/26 09:46:00 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// -- LIBRARIES --
# include "minishell.h"

// -- PROTOTYPES --
int				ft_handle_quote(char *str, int i, char quote);
t_token_type	ft_check_string_token(int c);
int				ft_handle_token(t_lexer *lexer, char *str, int i);
int				ft_get_word(char *str, int i, t_lexer *lexer);

t_lexer			*ft_init_lexer(void);
int				ft_add_lexer(char *str, t_token_type type, t_lexer *lexer);

void			ft_lexer(t_exec *ex);

void			ft_debug_lexer(t_lexer *lexer);

void			ft_free_lexer(t_exec *ex);
void			ft_lexer_error(t_exec *ex, char *str);

#endif

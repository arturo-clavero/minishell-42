/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:04:06 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 23:33:55 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// -- LIBRARIES --
# include "minishell.h"

// -- STRUCTURES --

/**
 * @brief Structure for the lexer
 *
 * @param char *input - The input string
 * @param int token - The tokens list
 * @param int pos - The position in the input string
 */
typedef struct s_lexer
{
	char			*input;
	int				token;
	int				pos;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

// -- PROTOTYPES --
int					ft_skip_spaces(char *str, int i);
int					ft_tokens(int c);
int					ft_quotes(char *str, int i, char quote);
int					ft_lexer(char *str, int i, t_lexer **lexer);

#endif

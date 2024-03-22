/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 21:58:38 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/22 14:36:24 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// -- COMMON
#define ERROR_MALLOC "minishell: Malloc cannot allocate memory."
#define ERROR_NO_ARGS "minishell: no arguments."
#define ERROR_NO_CLOSE_QUOTE "minishell: syntax error: unexpected end of file."

// -- LEXER --
#define ERROR_LENGTH_WORD "Error: Word exceeds maximum length\n"

// -- PARSER --
#define ERROR_INVALID_TOKEN "minishell: syntax error: invalid token\n"

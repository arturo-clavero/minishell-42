/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:06:13 by artclave          #+#    #+#             */
/*   Updated: 2024/03/16 10:14:22 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -- LIBRARIES --
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdint.h>
# include <termios.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

// -- CUSTOM LIBRARIES --
# include "../libs/includes/libft.h"
# include "messages.h"
# include "colors.h"
# include "executor.h"
# include "builtins.h"
# include "parser.h"
# include "lexer.h"
# include "expander.h"
# include "utils.h"

// -- DEFINES --
// # define PIPE 0
// # define OUTFILE 1
// # define APPEND 2
// # define INFILE 3
// # define HEREDOC 4

#endif

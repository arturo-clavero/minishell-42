/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:06:13 by artclave          #+#    #+#             */
/*   Updated: 2024/03/09 13:59:55 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -- LIBRARIES --
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libs/includes/libft.h"
# include "executor.h"
# include "builtins.h"
# include "utils.h"

// -- DEFINES --
# define PIPE 0
# define OUTFILE 1
# define APPEND 2
# define INFILE 3
# define HEREDOC 4

#endif

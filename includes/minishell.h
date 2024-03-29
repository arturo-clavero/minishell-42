/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uolle <uolle@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 04:06:13 by artclave          #+#    #+#             */
/*   Updated: 2024/03/29 18:59:10 by uolle            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -- LIBRARIES --
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>

// -- CUSTOM LIBRARIES --
# include "../libs/includes/libft.h"
# include "colors.h"
# include "messages.h"
# include "executor.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "utils.h"

// -- GLOBAL VARIABLES --
extern int	g_exit_status;

// -- PROTOTYPES --
void			ft_launch_minishell(t_exec *ex);
void			ft_signal_quit(int sig);
void			ft_handle_quit_signal(int sig);
void			ft_init_signals(void);

#endif

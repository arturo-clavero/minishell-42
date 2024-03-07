/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:03:36 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 21:40:24 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

// -- LIBRAIRIES --
# include "minishell.h"

// -- DEFINES --
# define SUCCESS 0

# define NO_PIPE -1
# define MAX_PATH_LINUX 4096
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define TRUE 1
# define FALSE 0

// -- STRUCTURES --
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_redir
{
	int				type;
	char			*file_name;
	char			*heredoc_buff;
	int				duplication;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**array;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;
typedef struct s_exec
{
	t_cmd			*cmd;
	t_list			*env_list;
	int				**fd;
	int				*id;
	int				total_pipes;
	int				total_children;
	int				stdin_original;
	int				stdout_original;
	char			*program_path;
	int				exit;
	t_list			*short_term_data;
	t_list			*long_term_data;
	t_list			*shell_env_list;
	int				is_builtin_last;
}					t_exec;

#endif

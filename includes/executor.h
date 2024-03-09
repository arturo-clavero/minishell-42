/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:03:36 by artclave          #+#    #+#             */
/*   Updated: 2024/03/09 14:02:38 by ugolin-olle      ###   ########.fr       */
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

// -- POST EXECUTION PROTOTYPES --
int					is_executable_minishell(char *cmd, t_exec *ex);
int					change_shlvl(int change, t_exec *ex);
void				adjust_shlvl(t_cmd *cmd, t_exec *ex);
void				get_previous_shells_env(t_exec *ex);
void				wait_for_child_exit_status(t_exec *ex);
void				maybe_quit_program(t_exec *ex);
void				exit_minishell(t_exec *ex, int exit_num);
void				clean_list(t_list *list, int clean_content);
void				clean_t_cmd(t_cmd *cmd);
void				add_data_to_cleanup_list(void *content, t_list **list);

// -- PREPARE EXECUTION PROTOTYPES --
void				initialize_minishell(t_exec *ex, char **env);
void				execution_main(t_exec *ex);
void				handle_dollar_sign(t_cmd **cmd_ptr, t_exec *ex);
void				create_pipes(t_cmd *cmd, t_exec *ex);
void				create_child_ids(t_cmd *cmd, t_exec *ex);

// -- PROCESS EXECUTION PROTOTYPES --
void				process_cmds(t_cmd *cmd, t_exec *ex);
void				execute_command(int id, int curr_cmd, t_cmd *cmd,
						t_exec *ex);
void				close_open_pipes(int curr_cmd, t_exec *ex);
void				save_original_io(t_exec *ex);
void				reset_io(t_exec *ex);
void				dup_pipes(int curr_cmd, t_cmd *cmd, t_exec *ex);
void				dup_file_input(t_cmd *cmd);
void				dup_file_output(t_cmd *cmd);
int					are_redirections_valid(t_cmd *cmd);
int					open_file(t_redir *redir, int pipe_fd);

// -- UTILS EXECUTION PROTOTYPES --
void				new_node(void *content, t_list **list);
t_list				*get_last_node(t_list *list);
char				*get_env_value(char *variable, t_list *env_list);
t_list				*get_env_node(char *variable, t_exec *ex);
int					free_data(char *should_exit, char *data, int exit_code);
void				print_error(char *str1, char *str2, char *str3);
int					malloc_error(void);
void				skip_whitespace(char *str, int *i);
int					has_pipe(t_cmd *cmd);

#endif

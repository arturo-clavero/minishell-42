/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:42:32 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/17 00:48:44 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

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

/**
 * @brief The t_token_type enum
 *
 * @param PIPE - The pipe token
 * @param INFILE - The input file token
 * @param OUTFILE - The output file token
 * @param APPEND - The append file token
 * @param HEREDOC - The heredoc token
 * @param WORD - The word token
 * @return void
 */
typedef enum e_token_type
{
	UNINITIALIZED,
	WORD,
	PIPE,    // |
	INFILE,  // <
	OUTFILE, // >
	APPEND,  // >>
	HEREDOC, // <<
}					t_token_type;

/**
 * @brief The t_lexer structure
 *
 * @param char *str - The string
 * @param t_token_type token - The token type
 * @param int i - The index
 * @param struct s_lexer *next - The next node
 * @param struct s_lexer *prev - The previous node
 * @return void
 */
typedef struct s_lexer
{
	char			*str;
	t_token_type	token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}					t_lexer;

/**
 * @brief The t_list structure
 *
 * @param void *content - The content of the node
 * @param struct s_list *next - The next node
 * @return void
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief The t_redir structure
 *
 * @param int type - The redirection type
 * @param char *file_name - The file name
 * @param char *heredoc_buff - The heredoc buffer
 * @param int duplication - The file descriptor duplication
 * @param struct s_redir *next - The next redirection
 * @return void
 */
typedef struct s_redir
{
	int				type;
	char			*file_name;
	char			*heredoc_buff;
	int				duplication;
	struct s_redir	*next;
}					t_redir;

/**
 * @brief The t_cmd structure
 *
 * @param char **array - The command array
 * @param t_redir *redir - The redirections
 * @param struct s_cmd *next - The next command
 * @return void
 */
typedef struct s_cmd
{
	char			**array;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

/**
 * @brief The t_exec structur
 *
 * @param t_cmd *cmd - The command structure
 * @param t_list *env_list - The environment list
 * @param int **fd - The file descriptors
 * @param int *id - The child process id
 * @param int total_pipes - The total number of pipes
 * @param int total_children - The total number of children
 * @param int stdin_original - The original stdin
 * @param int stdout_original - The original stdout
 * @param char *program_path - The program path
 * @param int exit - The exit status
 * @param t_list *short_term_data - The short term data
 * @param t_list *long_term_data - The long term data
 * @param t_list *shell_env_list - The shell environment list
 * @param int is_builtin_last - The last command is a builtin
 * @return void
 */
typedef struct s_exec
{
	char			*args;
	t_lexer			*lexer;
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
void				execution_main(t_cmd *cmd, t_exec *ex);
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

#endif

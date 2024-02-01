/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 02:03:36 by artclave          #+#    #+#             */
/*   Updated: 2024/02/01 18:33:39 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>

# define SUCCESS 0

# define NO_PIPE -1
# define MAX_PATH_LINUX 4096
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define TRUE 1
# define FALSE 0

//we should have the same values for these:
# define PIPE 0
# define OUTFILE 1
# define APPEND 2
# define INFILE 3
# define HEREDOC 4

//I mean I am not sure why this is here I guess we can get rid of this struct and just leave it as
//char name and char heredoc_buff in t_Redir
//but anyways name is name of the file, heredoc_buff is the text of the heredoc
typedef struct s_file
{
	char	*name;
	char	*heredoc_buff;
}		t_file;

//list of redirections so in my code I set type like PIPE, OUTFILE, APPEND etc from the defines above
//I don't care about the values of these so we can change their numerical value if needed
//int duplication is STDIN_FILENO for input, and STDOUT_FILENO for output,
//it's specially necessary for pipes
typedef struct s_redir
{
	int				type;
	t_file			file;
	int				duplication;
	struct s_redir	*next;
}		t_redir;

//List for commands, each command node stores a command array
//if ls the array is {"ls", NULL}; if ls -l the array is {"ls", "-l", NULL}
//Commands are either one node (single command) or multiple nodes (comands and redirections
//separated by pipes)
//t_redir is list of redirections, first node to last -> redirections from left to right
typedef struct s_cmd
{
	char			**array;
	t_redir			*redir;
	struct s_cmd	*next;
}		t_cmd;

//THESE STRUCTURES NOW ARE JUST FOR EXECUTION DON'T WORRY ABOUT THEM
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}		t_list;


typedef struct s_exec
{
	t_cmd	*cmd;
	int		exit;
	int		**fd;
	int		total_pipes;
	int		*id;
	t_list	*env_list;
	t_list	*id_list;
}		t_exec;

void	initialize_minishell(t_exec *ex, char **env);
void	execution(t_exec *ex);
void	create_process_ids(t_cmd *cmd, t_exec *ex);
void	create_pipe_fds(t_cmd *cmd, t_exec *ex);
void	piped_commands(t_cmd *cmd, t_exec *ex);
void	last_command(t_cmd *cmd, t_exec *ex);
void	check_redirections_for_curr_cmd(t_cmd *cmd);
void	close_all_pipes(int **fd, int total_pipes);
void	dup_input(t_cmd *cmd, int pipe_fd);
void	dup_output(t_cmd *cmd, int pipe_fd);
int		open_file(t_redir *redir, int pipe_fd);
int		write_heredoc_to_pipe(char *buffer);
void	execute_command(t_cmd *cmd, t_exec *ex);
char	*get_cmd_path_for_exec(char **cmd_array, char **env);
void	get_exit_status(t_exec *ex);
void	new_node(void *content, t_list **list);
t_list	*get_last_node(t_list *list);
void	skip_whitespace(char *str, int *i);
int		is_digit(char c);
int		is_letter(char c);
void	check_built_ins(t_cmd *cmd, char **cmd_array, t_exec *ex);
void	exec_cd(t_cmd *cmd, char **cmd_array, t_exec *ex);
void	cd_with_no_arguments(char **new_dir, char *pwd);
void	update_env(char *variable_name, char *new_env, t_list *env_list);
void	update_node_content(char *variable_name, char *new_value, t_list **env_list);
void	exec_pwd(void);
void	exec_echo(char **cmd_array);
int		is_nflag(char *str);
void	exec_export(char **cmd_array, t_exec *ex);
int		is_export_syntax_valid(char *cmd_array, char *original_cmd);
void	handle_dollar_sign(t_cmd **cmd, t_exec *ex);
void	sub_expandable(char **str, int start, int end, t_exec *ex);
int		is_variable_content_valid(char *cmd_array, char *original_cmd);
int		is_variable_start_valid(char *cmd_array, char *original_cmd);
void	print_env_alphabetically(t_list *env, t_list *head);
int		next_smallest_string(t_list *env, char *new_min, char *old_min);
void	add_slash_to_inside_double_quotes(char **str, int len);
void	add_quotes_around_value(char **str);
int		has_unclosed_quotes(char *str, char *original_cmd);
void	delete_outside_quotes(char **str);
void	delete_char_from_str(int delete, char **str);
void	exec_unset(char **cmd_array, t_exec *ex);
void	check_unset_syntax(char **cmd_array);
void	delete_node(t_list *node_delete, t_list **head);
void	exec_env(t_exec *ex);
void	exec_exit(char **cmd_array, t_exec *ex);

#endif

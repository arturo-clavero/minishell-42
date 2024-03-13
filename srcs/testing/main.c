/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:35:42 by artclave          #+#    #+#             */
/*   Updated: 2024/03/13 23:04:51 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*get_last_redir_node(t_redir *redir)
{
	while (redir->next)
		redir = redir->next;
	return (redir);
}

t_cmd	*get_last_command_node(t_cmd *cmd)
{
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*new_command_node(t_cmd **cmd)
{
	t_cmd	*new_node;
	t_cmd	*prev_node;

	new_node = malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL); //HANDLE ERROR
	memset(new_node, 0, sizeof(t_cmd));
	if (*cmd == NULL)
		*cmd = new_node;
	else
	{
		prev_node = get_last_command_node(*cmd);
		prev_node->next = new_node;
	}
	return (new_node);
}


t_redir	*new_redirect_node(t_redir **redir)
{
	t_redir	*new_redir;
	t_redir	*prev_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL); //HANDLE ERROR
	memset(new_redir, 0, sizeof(t_redir));
	if (*redir == NULL)
		*redir = new_redir;
	else
	{
		prev_redir = get_last_redir_node(*redir);
		prev_redir->next = new_redir;
	}
	return (new_redir);
}


void	get_redirection_nodes(t_redir **redir_node, char ***str_array, int i)
{
	t_redir	*new_redir_node;
	int		j;
	int		f;

	//1 . CHECK FOR INPUT PIPE
	//if we have multiple commands all commands except the first one will have an input pipe
	// cmd1 | cmd2 | cmd3 | cmd4
	// if cmd1 has an index of 0, it is the only one that doesn't have a pipe to the left (input pipe)
	//if index is bigger than 0 we know to create an input pipe as the first redirection node
	if (i > 0)
	{
		new_redir_node = new_redirect_node(redir_node);
		new_redir_node->type = PIPE;
		new_redir_node->duplication = STDIN_FILENO;
		new_redir_node->next = NULL;
	}
	
	//2. CHECK FILE REDIRECTIONS (> file_name)
	//Now we should create redir nodes in the order we find them, from left to right in the string
	//We are also going to delete the redirection symbol and file name, as we create redir nodes,
	//so that at the end we should be left with the cmd string that is sent to execve function for execution
	//the goal is to change "echo >file1 hello >file2 world" to "echo hello world"
	//(for simplicity) in this parsing we are ONLY going to identify symbol > 
	// we will also assume that filename is always to the right of > (this will not always be the case just for simple parsing)
	j = -1;
	while ((*str_array)[i][++j])
	{
		if ((*str_array)[i][j] == '>')
		{
			new_redir_node = new_redirect_node(redir_node);
			new_redir_node->type = OUTFILE;
			(*str_array)[i][j] = '\0';
			j++;
			while ((*str_array)[i][j] && ((*str_array)[i][j] == ' ' || (*str_array)[i][j] == '\t'))
				j++;
			f = j;
			while ((*str_array)[i][f] && ((*str_array)[i][f] != ' ' && (*str_array)[i][f] != '\t'))
				f++;
			(*str_array)[i][f] = '\0';
			new_redir_node->file_name = ft_strdup(&(*str_array)[i][j]);
			new_redir_node->duplication = STDOUT_FILENO;
			new_redir_node->next = NULL;
			(*str_array)[i][f] = '\0';
			if ((*str_array)[i][f] && (*str_array)[i][f + 1])
				f++;
			(*str_array)[i][j] = '\0';
			ft_strcat((*str_array)[i], &(*str_array)[i][f]);
			j = f;
		}
	}

	//3. CHECK FOR OUTPUT FILE
	//if our command is not the last one then we know the last redir node will be an output pipe
	// cmd1 ->it is the first but also last cmd so there is no pipe after it
	//cmd1 | cmd2 | cmd3 ->last cmd is cmd3 thus it is the only one with no pipe after it (no output pipe)
	//so we will check if the next cmd_str of the next index i exists, basically checking if any commands after thus one
	if ((*str_array)[++i])
	{
		new_redir_node = new_redirect_node(redir_node);
		new_redir_node->type = PIPE;
		new_redir_node->duplication = STDOUT_FILENO;
		new_redir_node->next = NULL;
		
	}	
}

void	simple_parsing(char *input, t_cmd **cmd_head)
{
	char	**cmd_str_array;
	int		i;
	t_redir	*redir_node;
	t_cmd	*new_cmd_node;

	cmd_str_array = ft_split(input, '|'); //now each cmd_str_array[i] will be transformed to a t_cmd node
	i = -1;
	while (cmd_str_array[++i])
	{
		redir_node = NULL;
		get_redirection_nodes(&redir_node, &cmd_str_array, i);
		new_cmd_node = new_command_node(cmd_head);
		new_cmd_node->array = ft_split(cmd_str_array[i], ' ');
		new_cmd_node->redir = redir_node; 
		new_cmd_node->next = NULL;
		free(cmd_str_array[i]);
	}
	free(cmd_str_array);
}

void	print_nodes(t_cmd *cmd_head)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	cmd = cmd_head;
	j = 1;
	while (cmd)
	{
		i = -1;
		printf("cmd%d:", j);
		while (cmd->array[++i])
			printf(" %s", cmd->array[i]);
		printf("\n");
		i = 1;
		if (cmd->redir == NULL)
			printf("redir: NONE\n");
		else
		{
			while (cmd->redir)
			{
				if (cmd->redir->type == PIPE)
				{
					printf("redir%d = %s", i, "pipe");
					if (cmd->redir->duplication == STDOUT_FILENO)
						printf(" (output)\n");
					else
						printf(" (input)\n");
				}
				if (cmd->redir->type == OUTFILE)
					printf("redir%d = %s, [%s]\n", i, "outfile (output)", cmd->redir->file_name);
				cmd->redir = cmd->redir->next;
				i++;
			}
		}
		cmd = cmd->next;
		printf("\n\n");
		j++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_exec	ex;
	t_cmd	*cmd;
	char	*input;


	(void)av;
	(void)ac;
	initialize_minishell(&ex, env);
	while (1)
	{
		input = readline("minishell: ");
		if (!input)
			exit_minishell(&ex, ex.exit);
		if (*input)
			add_history(input);
		else
			continue ;
		cmd = NULL;
		simple_parsing(input, &cmd);
	//	print_nodes(cmd);
		expand_each_cmd_node(&cmd, &ex);
		execution_main(cmd, &ex);
		free(input);
	}
	return (SUCCESS);
}
*/
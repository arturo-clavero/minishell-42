/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:58:52 by artclave          #+#    #+#             */
/*   Updated: 2024/03/24 03:53:41 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_smallest_string(t_list *env, char *new_min, char *old_min);

/**
 * @brief checks syntax of the first char of variable name
 * 
 * @param char *cmd_array - current string being modified
 * @param char *orginal_cmd - initial string prior to any modifications
 * @return int (0) no errors, (1) errors
 */
int	is_variable_start_valid(char *cmd_array, char *original_cmd)
{
	int	j;

	(void)original_cmd;
	j = 0;
	if (!ft_isalpha(cmd_array[j]) && cmd_array[j] != '_')
	{
		print_error("export `", cmd_array, "': not a valid identifier");
		return (1);
		//return (free_data(NULL, original_cmd, 1));
	}
	return (0);
}

/**
 * @brief checks syntax of variable name
 * 
 * @param char *cmd_array - current string being modified
 * @param char *original_cmd - initial string prior to any modifications
 * @return int (0) no errors, (1) errors
 */
int	is_variable_content_valid(char **cmd, char *original_cmd)
{
	int	j;

	j = 0;	
		(void)original_cmd;

	while ((*cmd)[j] && (*cmd)[j] != '=')
	{
		/*if ((*cmd)[j] == '+' && (*cmd)[j + 1]
			&& (*cmd)[j + 1] == '=')
		{
			delete_char_from_str(j, cmd);
			j--;
			and add value to added value Test 30
		}
		else */

		if (!ft_isalpha((*cmd)[j]) && !ft_isnum((*cmd)[j])
			&& (*cmd)[j] != '_')
		{
			print_error("export `", *cmd, "': not a valid identifier");
			return (1);
		//	return (free_data(NULL, original_cmd, 1));
		}
		j++;
	}
	return (0);
}

/**
 * @brief	prints environment list in alphabetical order 
 * 
 * @param t_list *env - environment list
 * @param t_list *head - copy of environment list
 * @return void
 */
void	print_env_alphabetically(t_list *env, t_list *head)
{
	char	*new_min;
	char	*old_min;

	new_min = ((char *)env->content);
	old_min = NULL;
	while (1)
	{
		env = head;
		if (old_min)
			new_min = NULL;
		while (env)
		{
			if (next_smallest_string(env, new_min, old_min))
				new_min = ((char *)env->content);
			env = env->next;
		}
		if (new_min == NULL)
			break ;
		printf("declare -x %s\n", new_min);
		old_min = new_min;
	}
}

/**
 * @brief checks if new_min should be printed next
 * 
 * @param t_list *env - environment list
 * @param char *new_min - next possible string to be printed
 * @param char *old_min - last string printed
 * @return int
 */

static int	next_smallest_string(t_list *env, char *new_min, char *old_min)
{
	char	*next_str;
	int		len;

	next_str = ((char *)env->content);
	len = ft_strlen(next_str);
	if (!new_min || ft_strncmp(next_str, new_min, len) < 0)
	{
		if (!old_min || ft_strncmp(next_str, old_min, len) > 0)
			return (TRUE);
	}
	return (FALSE);
}

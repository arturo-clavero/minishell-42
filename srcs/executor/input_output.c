/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 07:03:24 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 10:32:26 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Save the original input and output.
 *
 * @param t_exec *ex - The execution
 * @return void
*/
void	save_original_io(t_exec *ex)
{
	ex->stdin_original = dup(STDIN_FILENO);
	ex->stdout_original = dup(STDOUT_FILENO);
}

/**
 * @brief Reset the input and output.
 *
 * @param t_exec *ex - The execution
 * @return void
*/
void	reset_io(t_exec *ex)
{
	dup2(ex->stdin_original, STDIN_FILENO);
	close(ex->stdin_original);
	dup2(ex->stdout_original, STDOUT_FILENO);
	close(ex->stdout_original);
}
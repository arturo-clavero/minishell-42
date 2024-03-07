/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 05:34:17 by artclave          #+#    #+#             */
/*   Updated: 2024/03/07 21:47:00 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREP_EXEC_H
# define PREP_EXEC_H

// -- LIBRARIES --
# include "minishell.h"

// -- PROTOTYPES --
void	initialize_minishell(t_exec *ex, char **env);
void	execution_main(t_exec *ex);
void	handle_dollar_sign(t_cmd **cmd_ptr, t_exec *ex);
void	create_pipes(t_cmd *cmd, t_exec *ex);
void	create_child_ids(t_cmd *cmd, t_exec *ex);

#endif

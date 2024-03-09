/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:08 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/08 09:58:29 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// -- LIBRAIRIES --
# include "minishell.h"

// -- PROTOTYPES --
void	ft_exit(char *content, int status);
char	*ft_strjoin_with_sep(char const *s1, char const *s2, char sep);
void	ft_init_exec(t_exec *ex, char **env);

#endif

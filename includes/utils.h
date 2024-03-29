/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:55:08 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/29 19:16:01 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// -- LIBRAIRIES --
# include "minishell.h"

// -- PROTOTYPES --
void	ft_exit(char *content, int status);
char	*ft_strjoin_with_sep(char const *s1, char const *s2, char sep);
int		ft_isnum(char str);
int		ft_is_numericable(char *str);
void	ft_print_cmd(t_cmd *cmd);
char	*ft_join_3_strings(char *str1, char *str2, char *str3);
char	*ft_get_pid(void);
int		double_strncmp(char *str1, char *str2);
char	**ft_list_to_str_array(t_list *lst);
int		ft_count_quotes(char *str);
int		ft_is_space(int c);
void	clean_redir(t_redir	*redir);
void	new_value_error(char *og, char **new_value, t_exec *ex);
int		general_cd_error(char **og, char **buf, char **new_dir);

#endif

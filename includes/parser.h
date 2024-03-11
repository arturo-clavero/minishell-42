/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:24:30 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 12:19:11 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// -- LIBRARIES --
# include "minishell.h"

// -- PROTOTYPES --
t_cmd	*ft_parse_input(char *str);

#endif

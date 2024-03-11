/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:59:10 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 12:22:40 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle tokens in the string.
 *
 * @param char *str - The string to handle
 * @param int i - The index of the string
 * @param t_lexer **lexer - The lexer list
 * @return int
 */
int	ft_lexer(char *str, int i, t_lexer **lexer)
{
	(*lexer)->token = ft_tokens(str[i]);
	printf("Token: %d\n", (*lexer)->token);
	return (0);
}

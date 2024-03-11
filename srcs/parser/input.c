/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:26:59 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/11 13:17:04 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Split the input string into tokens.
 *
 * @param char *str - The input string
 * @return t_token* : The token list
 */
t_lexer	*ft_input(char *str)
{
	t_lexer	*lexer;
	int		i;

	lexer = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_lexer(str, i, &lexer) == -1)
			return (NULL);
		i++;
	}
	return (lexer);
}

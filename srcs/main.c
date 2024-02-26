/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugolin-olle <ugolin-olle@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:48:55 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/02/26 10:52:35 by ugolin-olle      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
	{
		printf("[ERROR] - Program does not take any arguments\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:32:31 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 09:33:53 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **argv)
{
	bool	printnl;
	int		start;

	printnl = true;
	start = 1;
	if (argv[1] && strcmp(argv[1], "-n") == 0)
	{
		printnl = false;
		start = 2;
	}
	for (int i = start; argv[i]; i++)
	{
		if (i > start)
			printf(" ");
		printf("%s", argv[i]);
	}
	if (printnl)
		printf("\n");
	return (0);
}

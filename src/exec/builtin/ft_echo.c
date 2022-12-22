/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:32:31 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 23:31:03 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_echo(char **argv)
{
	bool	printnl;
	int		start;
	int		i;

	printnl = true;
	start = 1;
	if (argv[1] && strcmp(argv[1], "-n") == 0)
	{
		printnl = false;
		start = 2;
	}
	i = start;
	while (argv[i])
	{
		if (i > start)
			ft_putstr_fd(" ", STDOUT_FILENO);
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
	}
	if (printnl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

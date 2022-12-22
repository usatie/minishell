/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:34:06 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 18:32:28 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static bool	is_numeric(const char *s)
{
	if (*s == '\0')
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int	ft_exit(char **argv)
{
	long	res;
	char	*s;
	char	*endptr;

	if (!argv[1])
		exit(g_env.status);
	if (argv[2])
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	s = argv[1];
	if (!is_numeric(s))
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(255);
	}
	errno = 0;
	res = ft_strtol(s, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
	{
		ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
		exit(255);
	}
	exit((int)res);
}

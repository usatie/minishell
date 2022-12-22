/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:25:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 08:51:15 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	print_all_variables(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
}

// Assignment string should be allocated and should not be freed.
static void	putenv_all(char **argv)
{
	char	*assignment;
	int		i;

	i = 1;
	while (argv[i])
	{
		assignment = ft_strdup(argv[i]);
		if (!assignment)
			fatal_exit("ft_strdup");
		if (ft_putenv(assignment) < 0)
			fatal_exit("ft_putenv");
		i++;
	}
}

int	ft_export(char **argv)
{
	if (argv[1] == NULL)
		print_all_variables();
	else
		putenv_all(argv);
	return (0);
}

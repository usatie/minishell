/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:25:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 17:23:33 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// assignment should not be freed.
// So it must be allocated and dismissed here.
static int	print_all_variables(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(environ[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

static int	putenv_all(char **argv)
{
	char	*assignment;
	int		i;

	i = 1;
	while (argv[i])
	{
		assignment = ft_strdup(argv[i]);
		if (!assignment)
			fatal_exit("ft_strdup");
		if (putenv(assignment) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(char **argv)
{
	if (argv[1] == NULL)
		return (print_all_variables());
	else
		return (putenv_all(argv));
}

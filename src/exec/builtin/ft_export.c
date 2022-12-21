/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:25:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 19:11:27 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

// assignment should not be freed.
// So it must be allocated and dismissed here.
int	ft_export(char **argv)
{
	char	*assignment;
	int		i;

	i = 1;
	while (argv[i])
	{
		assignment = strdup(argv[i]);
		if (!assignment)
			fatal_exit("strdup");
		if (putenv(assignment) < 0)
			return (1);
		i++;
	}
	return (0);
}

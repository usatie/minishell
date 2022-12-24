/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:24:54 by susami            #+#    #+#             */
/*   Updated: 2022/12/24 23:48:21 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	ft_unset(char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
	{
		if (ft_unsetenv(argv[i]) < 0)
			return (1);
		if (unsetenv_name(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

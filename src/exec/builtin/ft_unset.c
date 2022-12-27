/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:24:54 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:56:54 by susami           ###   ########.fr       */
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
		unsetenv_name(argv[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:34:06 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 16:52:49 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	ft_exit(char **argv)
{
	char	*arg;

	arg = argv[1];
	if (!arg)
		exit(g_env.status);
	if (argv[2] == NULL)
		exit(atoi(arg));
	ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
	return (1);
}

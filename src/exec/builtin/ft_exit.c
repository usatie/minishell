/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:34:06 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 13:41:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

int	ft_exit(char **argv)
{
	char	*arg;

	arg = argv[1];
	if (arg)
		exit(atoi(arg));
	else
		exit(g_env.status);
}

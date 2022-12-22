/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:24:31 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 23:31:43 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_env(char **argv)
{
	int	i;

	(void)argv;
	i = 0;
	while (environ[i])
		ft_putendl_fd(environ[i++], STDOUT_FILENO);
	return (0);
}

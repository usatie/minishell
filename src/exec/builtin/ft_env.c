/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:24:31 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 09:41:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_env(char **argv)
{
	char	**environ;
	int		i;

	(void)argv;
	environ = g_env.environ;
	i = 0;
	while (environ[i])
		ft_putendl_fd(environ[i++], STDOUT_FILENO);
	return (0);
}

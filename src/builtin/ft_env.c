/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 09:24:31 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 11:04:33 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_env(char **argv)
{
	(void)argv;
	for (int i = 0; environ[i]; i++)
		ft_putendl_fd(environ[i], STDOUT_FILENO);
	return (0);
}

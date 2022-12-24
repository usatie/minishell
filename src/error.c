/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:03:49 by susami            #+#    #+#             */
/*   Updated: 2022/12/24 09:52:36 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

#define PERROR_PREFIX "minishell: "

void	ft_perror(const char *s)
{
	write(STDERR_FILENO, PERROR_PREFIX, sizeof(PERROR_PREFIX));
	perror(s);
}

void	fatal_exit(char *s)
{
	ft_perror(s);
	exit(1);
}

void	err_exit(char *s)
{
	ft_perror(s);
	exit(127);
}

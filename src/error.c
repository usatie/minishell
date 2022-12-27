/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:03:49 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:09:04 by susami           ###   ########.fr       */
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

void	ft_custom_perror(const char *location, const char *error_msg)
{
	write(STDERR_FILENO, PERROR_PREFIX, sizeof(PERROR_PREFIX));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
}

void	fatal_exit(char *s)
{
	ft_perror(s);
	exit(1);
}

void	err_exit(const char *location, const char *error_msg, int status)
{
	ft_custom_perror(location, error_msg);
	exit(status);
}

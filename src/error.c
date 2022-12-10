/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:03:49 by susami            #+#    #+#             */
/*   Updated: 2022/12/10 00:37:07 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void	fatal_exit(char *s)
{
	write(STDERR_FILENO, s, strlen(s));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

void	err_exit(char *s)
{
	write(STDERR_FILENO, s, strlen(s));
	write(STDERR_FILENO, "\n", 1);
	exit(127);
}

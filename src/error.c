/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:03:49 by susami            #+#    #+#             */
/*   Updated: 2022/12/11 16:27:37 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	fatal_exit(char *s)
{
	perror(s);
	exit(1);
}

void	err_exit(char *s)
{
	perror(s);
	exit(127);
}

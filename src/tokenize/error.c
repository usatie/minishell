/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 22:04:23 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 22:06:05 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_error(char *msg, char **rest, char *line)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	while (*line)
		line++;
	*rest = line;
	g_env.tokenize_error = true;
}

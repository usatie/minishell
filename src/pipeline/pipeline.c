/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:16:43 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 17:19:10 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

t_pipeline	*new_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (pipeline == NULL)
		fatal_exit("ft_calloc()");
	cpy_pipe(pipeline->inpipe, (int []){STDIN_FILENO, -1});
	cpy_pipe(pipeline->outpipe, (int []){-1, STDOUT_FILENO});
	return (pipeline);
}

t_pipeline	*connect_pipeline(t_pipeline *lhs, t_pipeline *rhs)
{
	lhs->next = rhs;
	if (pipe(lhs->outpipe) < 0)
		fatal_exit("pipe()");
	cpy_pipe(rhs->inpipe, lhs->outpipe);
	return (lhs);
}

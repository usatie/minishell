/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:16:43 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:21:44 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_pipeline	*new_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (pipeline == NULL)
		fatal_exit("ft_calloc");
	pipeline->inpipe[0] = STDIN_FILENO;
	pipeline->inpipe[1] = -1;
	pipeline->outpipe[0] = -1;
	pipeline->outpipe[1] = STDOUT_FILENO;
	return (pipeline);
}

int	pipeline_len(t_pipeline *pipeline)
{
	if (pipeline == NULL)
		return (0);
	return (1 + pipeline_len(pipeline->next));
}

pid_t	pipeline_last_pid(t_pipeline *pipeline)
{
	if (pipeline == NULL)
		return (-1);
	while (pipeline->next)
		pipeline = pipeline->next;
	return (pipeline->pid);
}

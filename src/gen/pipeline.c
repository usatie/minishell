/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:16:43 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 08:47:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_pipeline	*new_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (pipeline == NULL)
		fatal_exit("ft_calloc()");
	pipeline->inpipe[0] = STDIN_FILENO;
	pipeline->inpipe[1] = -1;
	pipeline->outpipe[0] = -1;
	pipeline->outpipe[1] = STDOUT_FILENO;
	return (pipeline);
}

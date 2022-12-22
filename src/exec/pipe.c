/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:58:13 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 00:18:24 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//               pipe_from_terminal_stdin
// par __ child1
//     |    ||   pipe1
//     |_ child2
//     |    ||   pipe2
//     |_ child3
//               pipe_to_terminal_stdout
void	prepare_pipes_child(t_pipeline *pipeline)
{
	ft_close(pipeline->inpipe[1]); // write end is not necessary
	ft_close(pipeline->outpipe[0]); // read end is not necessary
	ft_dup2(pipeline->inpipe[0], STDIN_FILENO);
	ft_dup2(pipeline->outpipe[1], STDOUT_FILENO);
}

void	prepare_pipes_parent(t_pipeline *pipeline)
{
	if (pipeline->inpipe[0] != STDIN_FILENO)
		ft_close(pipeline->inpipe[0]); // inpipe is not necessary anymore
	ft_close(pipeline->inpipe[1]); // inpipe is not necessary anymore
}

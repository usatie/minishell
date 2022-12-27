/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:58:13 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 16:21:54 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cpy_pipe(int dst[2], int src[2]);
//               pipe_from_terminal_stdin
// par __ child1
//     |    ||   pipe1
//     |_ child2
//     |    ||   pipe2
//     |_ child3
//               pipe_to_terminal_stdout

// Assume inpipe is already set
void	prepare_pipes_before_fork(t_pipeline *pipeline)
{
	if (pipeline->next == NULL)
		return ;
	if (pipe(pipeline->outpipe) < 0)
		fatal_exit("pipe");
	cpy_pipe(pipeline->next->inpipe, pipeline->outpipe);
}

// Close unnecessary pipes for parent
void	prepare_pipes_parent(t_pipeline *pipeline)
{
	// If pipeline is the first children, inpipe is a tty.
	// Else, inpipe is a pipe.
	// Read end of inpipe will not be used
	if (pipeline->inpipe[1] != -1)
		close(pipeline->inpipe[0]);
	// Write end of outpipe will not be used
	if (pipeline->next)
		close(pipeline->outpipe[1]);
}

// Close unnecessary pipes for the child.
// Duplicate read end of inpipe to STDIN_FILENO.
// Duplicate write end of outpipe to STDOUT_FILENO.
void	prepare_pipes_child(t_pipeline *pipeline)
{
	// Read end of outpipe will not be used
	ft_close(pipeline->outpipe[0]);
	ft_dup2(pipeline->inpipe[0], STDIN_FILENO);
	ft_dup2(pipeline->outpipe[1], STDOUT_FILENO);
}

static void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:32:27 by susami            #+#    #+#             */
/*   Updated: 2022/12/11 16:31:18 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

t_pipeline	*new_pipeline(char **argv)
{
	t_pipeline	*pipeline;

	pipeline = calloc(1, sizeof(t_pipeline));
	if (pipeline == NULL)
		err_exit("calloc()");
	pipeline->argv = argv;
	cpy_pipe(pipeline->inpipe, (int []){STDIN_FILENO, -1});
	cpy_pipe(pipeline->outpipe, (int []){-1, STDOUT_FILENO});
	return (pipeline);
}

t_pipeline	*connect_pipeline(t_pipeline *lhs, t_pipeline *rhs)
{
	lhs->next = rhs;
	if (pipe(lhs->outpipe) < 0)
		err_exit("pipe()");
	cpy_pipe(rhs->inpipe, lhs->outpipe);
	return (lhs);
}

char	**gen_argv(t_node **rest, t_node *node)
{
	int		i;
	char	**argv;
	t_node	*arg;

	i = 0;
	argv = calloc(node->nargs + 1, sizeof(char *));
	arg = node->args;
	while (i < node->nargs)
	{
		argv[i] = convert_to_word(arg->str);
		arg = arg->next;
		i++;
	}
	// TODO: redirect
	*rest = node->next;
	return (argv);
}

t_pipeline	*gen_pipeline(t_node *node)
{
	if (node->kind == ND_CMD)
		return (new_pipeline(gen_argv(&node, node)));
	else if (node->kind == ND_PIPE)
	{
		return (connect_pipeline(gen_pipeline(node->lhs), gen_pipeline(node->rhs)));
	}
	err_exit("Unexpected Node\n");
}

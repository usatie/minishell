/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:32:27 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 17:03:41 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

t_pipeline	*new_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = calloc(1, sizeof(t_pipeline));
	if (pipeline == NULL)
		err_exit("calloc()");
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

char	**gen_argv(t_node *node)
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
	return (argv);
}

t_redirect	*new_redirect(char *path, int fd)
{
	t_redirect	*redirect;

	redirect = calloc(1, sizeof(t_redirect));
	if (!redirect)
		fatal_exit("calloc()");
	redirect->path = path;
	redirect->fd = fd;
	redirect->dupfd = -1;
	return (redirect);
}

t_redirect	*gen_redirect(t_node *redir_node)
{
	char	*path;
	int		fd;

	path = convert_to_word(redir_node->rhs->str);
	fd = redir_node->lhs->val;
	return (new_redirect(path, fd));
}

t_redirect	*add_redir_back(t_redirect *head, t_redirect *new_redir)
{
	t_redirect	*cur;
	
	if (!head)
		return (new_redir);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_redir;
	return (head);
}

t_pipeline	*gen_command(t_node *node)
{
	t_pipeline	*command;

	command = new_pipeline();
	command->argv = gen_argv(node);
	for (t_node	*redir_node = node->redir_out; redir_node; redir_node = redir_node->next)
	{
		command->redir_out = add_redir_back(command->redir_out, gen_redirect(redir_node));
	}
	return (command);
}

t_pipeline	*gen_pipeline(t_node *node)
{
	if (node->kind == ND_CMD)
		return (gen_command(node));
	else if (node->kind == ND_PIPE)
		return (connect_pipeline(gen_pipeline(node->lhs), gen_pipeline(node->rhs)));
	err_exit("Unexpected Node\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 14:32:27 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 17:19:11 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

char	**gen_argv(t_node *node)
{
	int		i;
	char	**argv;
	t_node	*arg;

	i = 0;
	argv = ft_calloc(node->nargs + 1, sizeof(char *));
	arg = node->args;
	while (i < node->nargs)
	{
		argv[i] = str_to_word(arg->str, true);
		arg = arg->next;
		i++;
	}
	return (argv);
}

t_redirect	*gen_redirect(t_node *node)
{
	int			fd;
	t_redirect	*rd;

	fd = node->lhs->val;
	if (node->kind == ND_REDIR_OUT)
		return (new_redirect(RD_OUTPUT, str_to_word(node->rhs->str, true), fd));
	else if (node->kind == ND_REDIR_IN)
		return (new_redirect(RD_INPUT, str_to_word(node->rhs->str, true), fd));
	else if (node->kind == ND_REDIR_APPEND)
		return (new_redirect(RD_APPEND, str_to_word(node->rhs->str, true), fd));
	else if (node->kind == ND_REDIR_HEREDOC)
	{
		rd = new_redirect(RD_HEREDOC, str_to_word(node->rhs->str, false), fd);
		rd->is_delim_quoted = is_any_quoted(node->rhs->str);
		return (rd);
	}
	else
		fatal_exit("Unexpected Node Kind");
}

t_pipeline	*gen_pipeline(t_node *node)
{
	t_pipeline	*command;
	t_node		*redir;

	command = new_pipeline();
	command->argv = gen_argv(node);
	redir = node->redirects;
	while (redir)
	{
		command->redirects = add_redir_back(command->redirects,
				gen_redirect(redir));
		redir = redir->next;
	}
	return (command);
}

t_pipeline	*gen(t_node *node)
{
	if (node->kind == ND_CMD)
		return (gen_pipeline(node));
	else if (node->kind == ND_PIPE)
		return (connect_pipeline(gen(node->lhs), gen(node->rhs)));
	fatal_exit("Unexpected Node\n");
}

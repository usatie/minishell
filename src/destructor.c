/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:33:42 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 18:46:40 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	free_str(t_str *str)
{
	if (!str)
		return ;
	free_str(str->next);
	free_str(str->parameters);
	free(str);
}

void	free_tok(t_token *tok)
{
	if (!tok)
		return ;
	free_tok(tok->next);
	free_str(tok->str);
	free(tok);
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	free_node(node->next);
	free_node(node->lhs);
	free_node(node->rhs);
	free_node(node->args);
	free_node(node->redirects);
	free(node);
}

static void	free_redirect(t_redirect *redirect)
{
	if (!redirect)
		return ;
	free_redirect(redirect->next);
	if (redirect->path)
		free(redirect->path);
	if (redirect->delimiter)
		free(redirect->delimiter);
	free(redirect);
}

static void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline)
		return ;
	free_pipeline(pipeline->next);
	free_redirect(pipeline->redirects);
	free_argv(pipeline->argv);
	free(pipeline);
}

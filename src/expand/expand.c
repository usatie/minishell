/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 06:45:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 11:59:04 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "minishell.h"

static void	foreach_str(t_str *s, void f(t_str *));

void	expand(t_node *node)
{
	if (!node)
		return ;
	if (node->kind == ND_REDIR_HEREDOC)
		expand(node->next);
	else
	{
		foreach_str(node->str, expand_str);
		expand(node->rhs);
		expand(node->lhs);
		expand(node->args);
		expand(node->redirects);
		expand(node->next);
	}
}

void	expand_str(t_str *s)
{
	char	*name;

	if (s->kind == STR_VAR)
	{
		if (s->value)
			return ;
		name = strndup(s->pos + 1, s->len - 1);
		s->value = getenv(name);
		if (s->value)
			s->value_len = strlen(s->value);
		free(name);
	}
	if (s->kind == STR_SPECIAL_PARAM)
	{
		if (startswith(s->pos, "$?"))
		{
			s->value = calloc(12, sizeof(char));
			sprintf(s->value, "%d", g_env.status);
			s->value_len = strlen(s->value);
		}
		else
			err_exit("Unexpected special param");
	}
	else if (s->kind == STR_DOUBLE)
		foreach_str(s->parameters, expand_str);
}

static void	foreach_str(t_str *s, void f(t_str *))
{
	while (s)
	{
		f(s);
		s = s->next;
	}
}

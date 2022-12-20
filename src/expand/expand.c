/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 06:45:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 08:35:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "minishell.h"

static void	expand_parameter_str(t_str *s);

static void	foreach_str(t_str *s, void f(t_str *))
{
	while (s)
	{
		f(s);
		s = s->next;
	}
}

void	expand(t_node *node)
{
	if (node->kind == ND_CMD)
	{
		for (t_node *arg = node->args; arg; arg = arg->next)
			foreach_str(arg->str, expand_parameter_str);
		for (t_node *redir = node->redirects; redir; redir = redir->next)
		{
			// If heredoc('<<' word), word is not expanded
			if (redir->kind == ND_REDIR_HEREDOC)
				continue;
			foreach_str(redir->rhs->str, expand_parameter_str);
		}
	}
	else if (node->kind == ND_PIPE)
	{
		expand(node->lhs);
		expand(node->rhs);
	}
}

static void	expand_parameter_str(t_str *s)
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
		foreach_str(s->parameters, expand_parameter_str);
}

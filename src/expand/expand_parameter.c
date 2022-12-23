/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:13:13 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 13:19:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	foreach_str(t_str *s, void f(t_str *));

void	expand_parameter(t_node *node)
{
	if (!node)
		return ;
	if (node->kind == ND_REDIR_HEREDOC)
		expand_parameter(node->next);
	else
	{
		foreach_str(node->str, expand_parameter_str);
		expand_parameter(node->rhs);
		expand_parameter(node->lhs);
		expand_parameter(node->args);
		expand_parameter(node->redirects);
		expand_parameter(node->next);
	}
}

void	expand_parameter_str(t_str *s)
{
	char	*name;

	if (s->kind == STR_VAR)
	{
		if (s->value)
			return ;
		name = ft_strndup(s->pos + 1, s->len - 1);
		s->value = getenv(name);
		if (s->value)
			s->value_len = ft_strlen(s->value);
		free(name);
	}
	if (s->kind == STR_SPECIAL_PARAM)
	{
		if (startswith(s->pos, "$?"))
		{
			s->value = ft_calloc(12, sizeof(char));
			sprintf(s->value, "%d", g_env.status);
			s->value_len = ft_strlen(s->value);
		}
		else
			err_exit("Unexpected special param");
	}
	else if (s->kind == STR_DOUBLE)
		foreach_str(s->parameters, expand_parameter_str);
}

static void	foreach_str(t_str *s, void f(t_str *))
{
	while (s)
	{
		f(s);
		s = s->next;
	}
}

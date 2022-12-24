/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 06:45:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/24 09:24:33 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "minishell.h"

void	expand(t_node *node)
{
	if (!node)
		return ;
	if (node->kind == ND_REDIR_HEREDOC)
		expand(node->next);
	else
	{
		expand_str(node->str);
		expand(node->rhs);
		expand(node->lhs);
		expand(node->args);
		expand(node->redirects);
		expand(node->next);
	}
}

static void	expand_variable(t_str *s)
{
	char	*name;

	if (s->value)
		return ;
	name = ft_strndup(s->pos + 1, s->len - 1);
	s->value = getenv(name);
	if (s->value)
		s->value_len = ft_strlen(s->value);
	free(name);
}

static void	expand_special_parameter(t_str *s)
{
	if (startswith(s->pos, "$?"))
	{
		s->value = ft_calloc(12, sizeof(char));
		sprintf(s->value, "%d", g_env.status);
		s->value_len = ft_strlen(s->value);
	}
	else
		fatal_exit("Unexpected special parameter");
}

void	expand_str(t_str *s)
{
	if (s == NULL)
		return ;
	if (s->kind == STR_VAR)
		expand_variable(s);
	else if (s->kind == STR_SPECIAL_PARAM)
		expand_special_parameter(s);
	else if (s->kind == STR_DOUBLE)
		expand_str(s->parameters);
	expand_str(s->next);
}

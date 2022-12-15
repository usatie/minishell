/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 06:45:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/15 13:35:05 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "minishell.h"

static void	expand_parameter_str(t_str *s);

void	expand_parameter(t_token *tok)
{
	while (tok->kind != TK_EOF)
	{
		if (tok->kind == TK_STRING)
		{
			for (t_str *s = tok->str; s; s = s->next)
				expand_parameter_str(s);
		}
		tok = tok->next;
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
			sprintf(s->value, "%d", status);
			s->value_len = strlen(s->value);
		}
		else
			err_exit("Unexpected special param");
	}
	else if (s->kind == STR_DOUBLE)
	{
		for (t_str *param = s->parameters; param; param = param->next)
			expand_parameter_str(param);
	}
}

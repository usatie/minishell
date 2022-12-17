/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 07:10:22 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 16:28:50 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "minishell.h"

t_token	*new_token(char *pos, size_t len, t_token_kind kind)
{
	t_token	*tok;

	tok = calloc(sizeof(t_token), 1);
	if (tok == NULL)
		fatal_exit("calloc()");
	tok->pos = pos;
	tok->len = len;
	tok->kind = kind;
	return (tok);
}

bool	startswith(const char *p, const char *q)
{
	return (memcmp(p, q, strlen(q)) == 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:59:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:00:38 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(const char *msg, t_token **rest, t_token *tok)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	while (!at_eof(tok))
		tok = tok->next;
	*rest = tok;
	g_env.syntax_error = true;
}

bool	equal(const t_token *tok, const char *op)
{
	return (ft_memcmp(tok->pos, op, tok->len) == 0 && op[tok->len] == '\0');
}

bool	at_eof(const t_token *tok)
{
	return (tok->kind == TK_EOF);
}

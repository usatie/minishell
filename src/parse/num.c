/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 22:12:51 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 22:13:37 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*num(t_token **rest, t_token *tok)
{
	t_node	*node;

	if (tok->kind == TK_NUM)
	{
		node = new_node_num(tok->val, tok);
		node->str = tok->str;
		*rest = tok->next;
		return (node);
	}
	// syntax error
	syntax_error("Invalid token for <num>", rest, tok);
	return (NULL);
}

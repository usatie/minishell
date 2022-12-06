/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/06 16:38:14 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

t_node	*new_node(char *cmd, char **argv)
{
	t_node	*node;

	node = calloc(sizeof(t_node), 1);
	node->cmd = cmd;
	node->argv = argv;
	return (node);
}

t_node	*parse(t_token *tok)
{
	char		*argv[100] = {};
	char		*cmd;
	size_t		i;

	// line = " cat -e Makefile"
	// tok->pos = "cat -e Makefile"
	// tok->len = 3
	while (tok->type == TK_PUNCT || tok->type == TK_SPACE)
		tok = tok->next;
	cmd = tok->content;
	i = 0;
	while (tok->type != TK_EOF)
	{
		if (tok->type == TK_PUNCT || tok->type == TK_SPACE)
		{
			tok = tok->next;
			i++;
			continue ;
		}
		if (argv[i] == NULL)
			argv[i] = tok->content;
		else
			argv[i] = ft_strjoin(argv[i], tok->content);
		tok = tok->next;
	}
	argv[i+1] = NULL;
	return (new_node(cmd, argv));
}

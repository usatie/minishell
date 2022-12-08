/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/08 22:20:57 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

t_command	*new_command(char **argv)
{
	t_command	*command;

	command = calloc(sizeof(t_command), 1);
	command->argv = argv;
	return (command);
}

t_command	*parse(t_token *tok)
{
	char		*argv[100] = {};
	size_t		i;

	// line = " cat -e Makefile"
	// tok->pos = "cat -e Makefile"
	// tok->len = 3
	i = 0;
	while (tok->type != TK_EOF)
	{
		if (tok->type == TK_SPACE)
		{
			if (argv[i])
				i++;
			tok = tok->next;
			continue ;
		}
		if (argv[i] == NULL)
			argv[i] = tok->content;
		else
			argv[i] = ft_strjoin(argv[i], tok->content);
		tok = tok->next;
	}
	argv[i+1] = NULL;
	return (new_command(argv));
}

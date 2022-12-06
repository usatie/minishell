/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:34:36 by susami            #+#    #+#             */
/*   Updated: 2022/12/06 15:43:07 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#include "libft.h"
#include "minishell.h"

t_node	*new_node(char *path, char **argv)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->path = path;
	node->argv = argv;
	return (node);
}

// find_path("cat") -> "/bin/cat"
char	*find_path(char *cmd)
{
	char	*path;
	char	*envpath;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = calloc(sizeof(char), PATH_MAX);
	envpath = getenv("PATH");
	paths = ft_split(envpath, ':');
	for (int i = 0; paths[i]; i++) {
		strcpy(path, paths[i]);
		strcat(path, "/");
		strcat(path, cmd);
		if (access(path, X_OK) == 0)
			return (path);
	}
	free(path);
	return (NULL);
}

t_node	*parse(t_token *tok)
{
	char		*argv[100];
	char		*path;
	size_t		i;

	// line = " cat -e Makefile"
	// tok->pos = "cat -e Makefile"
	// tok->len = 3
	while (tok->type == TK_PUNCT || tok->type == TK_SPACE)
		tok = tok->next;
	path = find_path(tok->content);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (tok)
	{
		if (tok->type == TK_PUNCT || tok->type == TK_SPACE)
		{
			tok = tok->next;
			continue ;
		}
		argv[i] = tok->content;
		i++;
		tok = tok->next;
	}
	argv[i] = NULL;
	return (new_node(path, argv));
}

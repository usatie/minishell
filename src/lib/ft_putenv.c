/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:56:29 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 09:33:05 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	find_environ_idx(char *name, size_t name_len)
{
	int		i;

	i = 0;
	while (g_env.environ[i])
	{
		if (ft_strncmp(g_env.environ[i], name, name_len) == 0
			&& g_env.environ[i][name_len] == '=')
			break ;
		i++;
	}
	return (i);
}

static int	internal_putenv(char *string, int i)
{
	char	**environ;

	environ = g_env.environ;
	if (environ[i])
	{
		free(environ[i]);
		environ[i] = string;
	}
	else
	{
		environ = (char **)ft_reallocf(environ, (i + 2) * sizeof(char *),
				i * sizeof(char *));
		if (environ == NULL)
			return (-1);
		environ[i] = string;
		environ[i + 1] = NULL;
		g_env.environ = environ;
	}
	return (0);
}

int	ft_putenv(char *string)
{
	char	*name_end;
	size_t	name_len;
	char	*name;
	int		idx;

	name_end = ft_strchr(string, '=');
	if (name_end == NULL)
	{
		ft_unsetenv(string);
		return (0);
	}
	name_len = name_end - string;
	name = ft_strndup(string, name_len);
	if (name == NULL)
		return (-1);
	idx = find_environ_idx(name, name_len);
	free(name);
	if (internal_putenv(string, idx) < 0)
		return (-1);
	return (0);
}

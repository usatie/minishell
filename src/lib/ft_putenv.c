/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:56:29 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 00:30:29 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static int	find_environ_idx(char *name, size_t name_len)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
			break ;
		i++;
	}
	return (i);
}

static int	internal_putenv(char *string, char *name, int i)
{
	extern char	**environ;

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
		{
			free(name);
			return (-1);
		}
		environ[i] = string;
		environ[i + 1] = NULL;
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
	return (internal_putenv(string, name, idx));
}

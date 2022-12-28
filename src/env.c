/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 14:47:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/28 14:48:05 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**environ_dup(void);

void	init_env(t_env *e)
{
	ft_bzero(e, sizeof(t_env));
	e->environ_name = ft_calloc(1, sizeof(char *));
	if (e->environ_name == NULL)
		fatal_exit("ft_calloc");
	e->environ = environ_dup();
}

// Never return NULL
static char	**environ_dup(void)
{
	extern char	**environ;
	char		**dup;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (dup == NULL)
		fatal_exit("ft_calloc");
	i = 0;
	while (environ[i])
	{
		dup[i] = ft_strdup(environ[i]);
		if (dup[i] == NULL)
			fatal_exit("ft_strdup");
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

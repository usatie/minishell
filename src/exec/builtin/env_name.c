/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:26:50 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 11:27:07 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	putenv_name(char *name)
{
	char	**environ_name;
	int		i;

	environ_name = g_env.environ_name;
	i = 0;
	while (environ_name[i])
	{
		if (ft_strcmp(environ_name[i], name) == 0)
			break ;
		i++;
	}
	// Already exists
	if (environ_name[i])
		return (0);
	// Insert
	environ_name = (char **)ft_reallocf(environ_name,
			(i + 2) * sizeof(char *), i * sizeof(char *));
	if (environ_name == NULL)
		return (-1);
	environ_name[i] = name;
	environ_name[i + 1] = NULL;
	g_env.environ_name = environ_name;
	return (0);
}

int	unsetenv_name(char *name)
{
	char	**environ_name;
	int		i;
	int		j;

	environ_name = g_env.environ_name;
	i = 0;
	while (environ_name[i])
	{
		if (ft_strcmp(environ_name[i], name) == 0)
		{
			j = i;
			while (environ_name[j])
			{
				environ_name[j] = environ_name[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (0);
}

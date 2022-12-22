/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:11:17 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 21:11:25 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minishell.h"

void	internal_unsetenv(char **ep)
{
	char	**sp;

	sp = ep;
	while (*sp)
	{
		*sp = *(sp + 1);
		sp++;
	}
}

int	ft_unsetenv(const char *name)
{
	size_t	len;
	char	**ep;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	len = ft_strlen(name);
	ep = environ;
	while (*ep)
	{
		if (ft_strncmp(*ep, name, len) == 0 && (*ep)[len] == '=')
			internal_unsetenv(ep);
		else
			ep++;
	}
	return (0);
}

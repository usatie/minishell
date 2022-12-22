/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:09:53 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 21:10:13 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "minishell.h"

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t	size;
	char	*es;

	if (name == NULL || name[0] == '\0' || ft_strchr(name, '=') != NULL
		|| value == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (getenv(name) != NULL && overwrite == 0)
		return (0);
	ft_unsetenv(name);
	size = ft_strlen(name) + ft_strlen(value) + 2;
	es = malloc(size);
	if (es == NULL)
		return (-1);
	ft_strlcpy(es, name, size);
	ft_strlcat(es, "=", size);
	ft_strlcat(es, value, size);
	if (ft_putenv(es) < 0)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:21:07 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 09:43:29 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char	**ep;
	size_t	name_len;

	ep = g_env.environ;
	name_len = ft_strlen(name);
	while (*ep)
	{
		if (ft_strncmp(name, *ep, name_len) == 0 && (*ep)[name_len] == '=')
			return (*ep + name_len + 1);
		ep++;
	}
	return (NULL);
}

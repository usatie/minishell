/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:35:03 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 16:12:35 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	*xgetenv(const char *s, size_t name_len)
{
	char	*name;
	char	*value;

	name = strndup(s, name_len);
	value = getenv(name);
	free(name);
	return (value);
}

char	*reallocf_strncat(char *dst, size_t *dst_size, char *src, size_t n)
{
	char	*newdst;

	newdst = ft_reallocf(dst, *dst_size + n, *dst_size);
	*dst_size += n;
	strncat(newdst, src, n);
	return (newdst);
}

char	*expand_line(char *line)
{
	char	*newline;
	size_t	size;
	char	*start;
	char	*value;

	size = 1;
	newline = calloc(size, sizeof(char));
	while (*line)
	{
		if (is_variable(line))
		{
			// $
			line++;
			start = line;
			while (is_alpha_num_under(*line))
				line++;
			value = xgetenv(start, line - start);
			if (value)
				newline = reallocf_strncat(newline, &size, value, strlen(value));
		}
		else
		{
			// "hello $USER"
			start = line;
			while (*line && *line != '$')
				line++;
			newline = reallocf_strncat(newline, &size, start, line - start);
		}
	}
	return (newline);
}

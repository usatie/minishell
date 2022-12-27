/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 20:22:34 by susami            #+#    #+#             */
/*   Updated: 2022/12/27 20:53:27 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_last(char *path);
static void	append(char *dst, size_t dstsize, char **rest, char *src);
static bool	consume(char **rest, char *path, const char *elem);
static bool	endswith(const char *p, const char *q);

void	resolve_filepath(char *dst, size_t dstsize, char *relpath)
{
	while (*relpath)
	{
		if (*relpath == '/')
			relpath++;
		else if (consume(&relpath, relpath, "./"))
			;
		else if (ft_strcmp(relpath, ".") == 0)
			relpath += 1;
		else if (consume(&relpath, relpath, "../"))
			delete_last(dst);
		else if (ft_strcmp(relpath, "..") == 0)
		{
			relpath += 2;
			delete_last(dst);
		}
		else
			append(dst, dstsize, &relpath, relpath);
	}
}

// Delete the last element of the path
static void	delete_last(char *path)
{
	int	i;
	int	last_slash_idx;

	last_slash_idx = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			last_slash_idx = i;
		i++;
	}
	if (last_slash_idx == 0)
		return ;
	path[last_slash_idx] = '\0';
}

bool	endswith(const char *p, const char *q)
{
	const char	*s1;
	const char	*s2;

	s1 = p;
	s2 = q;
	if (*p == '\0')
		return (*q == '\0');
	while (*p)
		p++;
	while (*q)
		q++;
	while (p != s1 && q != s2)
	{
		if (*p != *q)
			return (false);
		p--;
		q--;
	}
	return (*p == *q);
}

static void	append(char *dst, size_t dstsize, char **rest, char *src)
{
	int	len;

	len = 0;
	while (src[len] && src[len] != '/')
		len++;
	if (!endswith(dst, "/"))
		ft_strlcat(dst, "/", dstsize);
	ft_strncat(dst, src, len);
	*rest = src + len;
}

static bool	consume(char **rest, char *path, const char *elem)
{
	if (ft_strncmp(path, elem, ft_strlen(elem)) == 0)
	{
		*rest = path + ft_strlen(elem);
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:37:14 by susami            #+#    #+#             */
/*   Updated: 2022/06/16 14:16:08 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static int	get_fd_index(t_buf *b, int fd)
{
	int	i;

	i = 0;
	while (i < b->fd_len)
	{
		if (b->fds[i] == fd)
			return (i);
		i++;
	}
	if (i < FOPEN_MAX)
	{
		b->fds[i] = fd;
		b->rcs[i] = 0;
		b->fd_len++;
		return (i);
	}
	return (-1);
}

// returns negative on error
static int	read_to_buf_if_needed(t_buf *b, int fd, int i)
{
	if (b->cursors[i] != NULL && *(b->cursors[i]) != '\0')
		return (0);
	b->rcs[i] = read(fd, b->bufs[i], BUFFER_SIZE);
	if (b->rcs[i] < 0)
		return (-1);
	b->bufs[i][b->rcs[i]] = '\0';
	b->cursors[i] = b->bufs[i];
	return (0);
}

static size_t	len_to_cat(char *str)
{
	size_t	len;

	len = 0;
	while (*str && *str != '\n')
	{
		len++;
		str++;
	}
	if (*str == '\n')
		len++;
	return (len);
}

// s1 will always be freed even if on error.
static char	*strncat_reallocf(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	new_len;
	char	*new;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	new_len = s1_len + len_to_cat(s2) + 1;
	new = malloc(new_len);
	if (new == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	if (s1)
	{
		ft_strlcpy(new, s1, new_len);
		free(s1);
	}
	ft_strlcpy(new + s1_len, s2, len_to_cat(s2) + 1);
	return (new);
}

char	*get_next_line(int fd)
{
	static t_buf	b;
	char			*line;
	int				i;

	line = NULL;
	i = get_fd_index(&b, fd);
	if (i < 0)
		return (NULL);
	while (1)
	{
		if (read_to_buf_if_needed(&b, fd, i) < 0)
			return (NULL);
		else if (b.rcs[i] == 0)
			return (line);
		if (*b.cursors[i] != '\0')
		{
			line = strncat_reallocf(line, b.cursors[i]);
			if (line == NULL)
				return (NULL);
			b.cursors[i] += len_to_cat(b.cursors[i]);
			if (*(b.cursors[i] - 1) == '\n')
				return (line);
		}
		b.cursors[i] = NULL;
	}
}

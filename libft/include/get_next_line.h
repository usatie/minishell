/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:37:47 by susami            #+#    #+#             */
/*   Updated: 2022/06/16 11:02:54 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
// FOPEN_MAX is declared in <stdio.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_buf
{
	int		fd_len;
	int		fds[FOPEN_MAX];
	char	bufs[FOPEN_MAX][BUFFER_SIZE + 1];
	char	*cursors[FOPEN_MAX];
	ssize_t	rcs[FOPEN_MAX];
}	t_buf;

char	*get_next_line(int fd);

#endif

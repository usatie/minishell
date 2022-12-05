/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 09:54:12 by susami            #+#    #+#             */
/*   Updated: 2022/05/26 23:01:32 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// s: not protected (difference between "" and NULL is important)
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

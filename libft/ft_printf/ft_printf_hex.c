/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:53:11 by susami            #+#    #+#             */
/*   Updated: 2022/06/01 17:52:43 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

// enough for binary unsigned long long + "0x" or "0X" prefix
#define MAXBUF 66
#define BASE 16

void	print(t_fmt *fmt, char *str, size_t len);

void	puthex(unsigned long long n, unsigned long long capitals,
			char *prefix, t_fmt *fmt);

static void	set_buf_hex(char *buf, unsigned long long n,
	unsigned long long capitals, t_fmt *fmt)
{
	unsigned long long	x;
	char				*p;
	static char			digs[] = "0123456789abcdef0123456789ABCDEF";

	x = n;
	p = &buf[fmt->buf_len - 1];
	*p = digs[x % BASE + capitals];
	x /= BASE;
	while (x != 0)
	{
		*--p = digs[x % BASE + capitals];
		x /= BASE;
	}
}

// malloc, bzero, precision zero padding
static void	*init_buf(char *prefix, t_fmt *fmt)
{
	char	*buf;

	fmt->buf_len = MAXBUF;
	if ((size_t)fmt->precision > fmt->buf_len)
		fmt->buf_len = (size_t)fmt->precision;
	fmt->buf_len += ft_strlen(prefix);
	buf = ft_calloc(fmt->buf_len, sizeof(char));
	if (buf == NULL)
		fmt->out_size = -1;
	if ((fmt->flags & PRECISION_FLG) && fmt->precision > 0)
		ft_memset(buf + fmt->buf_len - (size_t)fmt->precision, '0',
			(size_t)fmt->precision);
	return (buf);
}

void	puthex(unsigned long long n, unsigned long long capitals,
	char *prefix, t_fmt *fmt)
{
	char	*buf;
	char	*p;
	size_t	len;

	buf = init_buf(prefix, fmt);
	if (buf == NULL)
		return ;
	set_buf_hex(buf, n, capitals, fmt);
	p = buf;
	len = fmt->buf_len;
	while (*p == 0)
	{
		p++;
		len--;
	}
	p -= ft_strlen(prefix);
	ft_memmove(p, prefix, ft_strlen(prefix));
	len += ft_strlen(prefix);
	if (n == 0 && (fmt->flags & PRECISION_FLG))
		len = (size_t)fmt->precision;
	print(fmt, p, len);
	free(buf);
}

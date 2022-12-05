/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 21:58:27 by susami            #+#    #+#             */
/*   Updated: 2022/07/28 18:40:06 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INT_MIN, INT_MAX
#include <limits.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

void	print(t_fmt *fmt, char *str, size_t len);
void	printf_di(t_fmt *fmt);
void	printf_u(t_fmt *fmt);

// enough for binary unsigned long long
#define MAXBUF 64
#define BASE 10

static void	set_buf_ull(char *buf, unsigned long long x, t_fmt *fmt)
{
	char			*p;
	static char		digs[] = "0123456789";

	p = buf + fmt->buf_len - 1;
	*p = digs[x % BASE];
	x /= BASE;
	while (x != 0)
	{
		*--p = digs[x % BASE];
		x /= BASE;
	}
}

// malloc, bzero, precision zero padding
static void	*init_buf(t_fmt *fmt)
{
	char	*buf;

	fmt->buf_len = MAXBUF;
	if ((size_t)fmt->precision > fmt->buf_len)
		fmt->buf_len = (size_t)fmt->precision;
	buf = ft_calloc(fmt->buf_len, sizeof(char));
	if (buf == NULL)
	{
		fmt->out_size = -1;
		return (NULL);
	}
	if ((fmt->flags & PRECISION_FLG) && fmt->precision > 0)
		ft_memset(buf + fmt->buf_len - fmt->precision, '0',
			(size_t)fmt->precision);
	return (buf);
}

static void	putull(unsigned long long x, t_fmt *fmt)
{
	char	*buf;
	char	*p;
	size_t	len;

	buf = init_buf(fmt);
	if (buf == NULL)
		return ;
	set_buf_ull(buf, x, fmt);
	p = buf;
	len = fmt->buf_len;
	while (*p == 0)
	{
		p++;
		len--;
	}
	if (x == 0 && (fmt->flags & PRECISION_FLG))
		len = (size_t)fmt->precision;
	print(fmt, p, len);
	free(buf);
}

void	printf_di(t_fmt *fmt)
{
	int		x;

	(fmt->format)++;
	x = va_arg(fmt->ap, int);
	if (fmt->flags & SIGN_SPACE_FLG)
		fmt->sign_c = ' ';
	if (fmt->flags & SIGN_PLUS_FLG)
		fmt->sign_c = '+';
	if (x < 0)
	{
		fmt->sign_c = '-';
		if (x == INT_MIN && INT_MIN + INT_MAX < 0)
			putull((unsigned long long)INT_MAX + 1, fmt);
		else
			putull((unsigned long long) -x, fmt);
	}
	else
	{
		putull((unsigned long long)x, fmt);
	}
}

void	printf_u(t_fmt *fmt)
{
	unsigned int	x;

	(fmt->format)++;
	x = va_arg(fmt->ap, unsigned int);
	putull(x, fmt);
}

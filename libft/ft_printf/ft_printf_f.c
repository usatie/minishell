/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 09:04:38 by susami            #+#    #+#             */
/*   Updated: 2022/10/07 16:54:48 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "ft_decimal.h"

void	ftoa(float f, char *res, int width, int precision);
void	dtoa(double f, char *res, int width, int precision);
void	print(t_fmt *fmt, char *str, size_t len);

void	printf_f(t_fmt *fmt);

#define BUF_SIZE	1500
#define DEFAULT_PRECISION	6

/*
 * At first, printf_f checks precision overflow by errno.
 * On non "%f" conversions like "%d", precision overflow is ok.
 * However, only on "%f" and "%lf", precision overflow must be handled.
*/
void	printf_f(t_fmt *fmt)
{
	double	d;
	char	*buf;

	(fmt->format)++;
	if (errno == EOVERFLOW)
	{
		fmt->out_size = -1;
		return ;
	}
	fmt->buf_len = BUF_SIZE;
	if ((size_t)fmt->precision > fmt->buf_len)
		fmt->buf_len = (size_t)fmt->precision + DOUBLE_MAX_INT + 2;
	buf = ft_calloc(fmt->buf_len, sizeof(char));
	if (buf == NULL)
	{
		fmt->out_size = -1;
		return ;
	}
	d = va_arg(fmt->ap, double);
	if (~fmt->flags & PRECISION_FLG)
		fmt->precision = DEFAULT_PRECISION;
	dtoa(d, buf, fmt->width, fmt->precision);
	print(fmt, buf, ft_strlen(buf));
	free(buf);
}

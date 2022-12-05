/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:02:19 by susami            #+#    #+#             */
/*   Updated: 2022/08/16 17:38:31 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	fmt_clear_spec(t_fmt *fmt);
void	fmt_init(t_fmt *fmt, const char *format);

void	fmt_clear_spec(t_fmt *fmt)
{
	fmt->conversion = 0;
	fmt->width = 0;
	fmt->precision = 0;
	fmt->flags = 0;
	fmt->sign_c = 0;
	fmt->buf_len = 0;
}

void	fmt_init(t_fmt *fmt, const char *format)
{
	ft_bzero(fmt, sizeof(t_fmt));
	fmt->format = format;
}

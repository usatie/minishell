/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:01:51 by susami            #+#    #+#             */
/*   Updated: 2022/09/02 22:01:41 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

void	fmt_init(t_fmt *fmt, const char *format);
void	fmt_clear_spec(t_fmt *fmt);
void	parse_flags(t_fmt *fmt);
void	parse_width(t_fmt *fmt);
void	parse_precision(t_fmt *fmt);
void	parse_conversion_spec(t_fmt *fmt);

void	print(t_fmt *fmt, char *str, size_t len);
void	print_non_conversion_bytes(t_fmt *fmt);

static int	ft_internal_printf(t_fmt *fmt)
{
	while (fmt->out_size > -1 && *(fmt->format))
	{
		fmt_clear_spec(fmt);
		if (*(fmt->format) == '%')
		{
			(fmt->format)++;
			parse_flags(fmt);
			parse_width(fmt);
			parse_precision(fmt);
			parse_conversion_spec(fmt);
		}
		else
			print_non_conversion_bytes(fmt);
	}
	if (fmt->out_size > 0)
		fmt->dst_str[fmt->out_size] = '\0';
	return (fmt->out_size);
}

int	ft_vsprintf(char *str, const char *format, va_list ap)
{
	t_fmt	fmt;

	if (format == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	fmt_init(&fmt, format);
	va_copy(fmt.ap, ap);
	fmt.dst_str_flags = STRING_FLG;
	fmt.dst_str = str;
	fmt.dst_str[0] = '\0';
	return (ft_internal_printf(&fmt));
}

/*
int	ft_vasprintf(char **ret, const char *format, va_list ap)
{
	t_fmt	fmt;

	if (format == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	fmt_init(&fmt, format);
	fmt.dst_str_flags = STRING_FLG | ALLOCATE_FLG;
	fmt.dst_str = NULL;
	fmt.ap = ap;
	ft_internal_printf(&fmt);
	*ret = fmt.dst_str;
	return (fmt.out_size);
}
*/

int	ft_sprintf(char *str, const char *format, ...)
{
	int		ret;
	va_list	ap;

	va_start(ap, format);
	ret = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (ret);
}

/*
int	ft_asprintf(char **ret, const char *format, ...)
{
	int		out_size;
	va_list	ap;

	va_start(ap, format);
	out_size = ft_vasprintf(ret, format, ap);
	va_end(ap);
	return (out_size);
}
*/

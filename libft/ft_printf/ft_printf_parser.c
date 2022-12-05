/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:34:31 by susami            #+#    #+#             */
/*   Updated: 2022/09/11 15:08:58 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include "libft.h"
#include "ft_printf.h"

void	parse_flags(t_fmt *fmt);
void	parse_width(t_fmt *fmt);
void	parse_precision(t_fmt *fmt);
void	parse_conversion_spec(t_fmt *fmt);

void	printf_percent(t_fmt *fmt);
void	printf_c(t_fmt *fmt);
void	printf_s(t_fmt *fmt);
void	printf_p(t_fmt *fmt);
void	printf_di(t_fmt *fmt);
void	printf_u(t_fmt *fmt);
void	printf_x_lower(t_fmt *fmt);
void	printf_x_upper(t_fmt *fmt);
void	printf_f(t_fmt *fmt);

typedef void	t_conv_f(t_fmt *);

static t_conv_f	*conversion_func(char c)
{
	if (c == '%')
		return (printf_percent);
	else if (c == 'c')
		return (printf_c);
	else if (c == 's')
		return (printf_s);
	else if (c == 'p')
		return (printf_p);
	else if (c == 'd' || c == 'i')
		return (printf_di);
	else if (c == 'u')
		return (printf_u);
	else if (c == 'x')
		return (printf_x_lower);
	else if (c == 'X')
		return (printf_x_upper);
	else if (c == 'f')
		return (printf_f);
	return (NULL);
}

/*	Overview of conversion specifiers
 
	start of conversion specifiers	: "%"
	flags							: "#-+ 0"
	width							: "20" "3"
	precision						: ".10" ".5"
	long							: "l"
	conversion specifier			: "%csdiupxX"

*/

void	parse_flags(t_fmt *fmt)
{
	char	c;

	while (1)
	{
		c = *(fmt->format);
		if (c == '#')
			fmt->flags |= ALT_FLG;
		else if (c == '-')
			fmt->flags |= PAD_RIGHT_FLG;
		else if (c == '+')
			fmt->flags |= SIGN_PLUS_FLG;
		else if (c == ' ')
			fmt->flags |= SIGN_SPACE_FLG;
		else
			break ;
		++(fmt->format);
	}
	if (c == '0')
	{
		fmt->flags |= PAD_ZERO_FLG;
		++(fmt->format);
	}
}

// "(x * 10 + y > INT_MAX)" is equivalent to "(x > (INT_MAX - y) / 10)"
// and no overflow/zero division unless y is less than INT_MAX
//
void	parse_width(t_fmt *fmt)
{
	char	c;

	c = *(fmt->format);
	while (ft_isdigit(c))
	{
		if (fmt->width > (INT_MAX - (c - '0')) / 10)
		{
			fmt->out_size = -1;
			errno = EOVERFLOW;
			return ;
		}
		fmt->width = fmt->width * 10 + (c - '0');
		++(fmt->format);
		c = *(fmt->format);
	}
}

void	parse_precision(t_fmt *fmt)
{
	char	c;

	c = *(fmt->format);
	if (c == '.')
	{
		fmt->flags |= PRECISION_FLG;
		fmt->precision = 0;
		(fmt->format)++;
		c = *(fmt->format);
		while (ft_isdigit(c))
		{
			if (fmt->precision > (INT_MAX - (c - '0')) / 10)
				errno = EOVERFLOW;
			fmt->precision = fmt->precision * 10 + (c - '0');
			++(fmt->format);
			c = *(fmt->format);
		}
	}
	if (fmt->precision < 0)
	{
		fmt->precision = 0;
		fmt->flags &= ~PRECISION_FLG;
	}
}

void	parse_conversion_spec(t_fmt *fmt)
{
	char		c;
	t_conv_f	*f;

	c = *(fmt->format);
	if (c == 'l')
	{
		fmt->flags |= LONG_FLG;
		(fmt->format)++;
		c = *(fmt->format);
	}
	f = conversion_func(c);
	if (f == NULL)
		return ;
	fmt->conversion = c;
	f(fmt);
}

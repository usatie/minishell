/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:42:36 by susami            #+#    #+#             */
/*   Updated: 2022/09/11 15:18:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ieee754.h"
#include "ft_decimal.h"

void				dtoa(double f, char *res, int width, int precision);
static t_decimal	ieee754_double_to_decimal(t_ieee754_double *f);
static void			parse_ieee754_double(t_ieee754_double *d,
						t_decimal *decimal, int *exponent);
static void			padzero(int pad, char *res);

/*
   Convert double value `d` to string `res`.
   `res` will be NULL terminated string.
   `width` is the total length of the result string.
   If result string is shorter than `width`, left side will be padded with 0.
   `precision` is the right side length not including dot.
   If `precision` is 0, then no dot will be added.

   The size of `res` must be >= max(FLT_MAX_INT + FLT_MAX_FRACT, width + 1).
*/
void	dtoa(double d, char *res, int width, int precision)
{
	t_ieee754_double	*ieee_d;
	t_decimal			decimal;

	ieee_d = (t_ieee754_double *)(&d);
	if (is_d_nan(*ieee_d))
	{
		ft_memmove(res, "nan", 4);
		return ;
	}
	if (is_d_negative(*ieee_d))
		*res++ = '-';
	if (is_d_inf(*ieee_d))
	{
		ft_memmove(res, "inf", 4);
		return ;
	}
	decimal = ieee754_double_to_decimal(ieee_d);
	decimal_to_str(decimal, res, precision);
	padzero(width - (int)ft_strlen(res), res);
}

// Convert number from ieee754_double to t_decimal without losing precision
static t_decimal	ieee754_double_to_decimal(t_ieee754_double *d)
{
	t_decimal	decimal;
	int			exponent;

	parse_ieee754_double(d, &decimal, &exponent);
	while (exponent != 0)
	{
		if (exponent > 0)
		{
			decimal = mul_decimal(decimal, 2);
			exponent--;
		}
		else
		{
			decimal = div_decimal(decimal, 2);
			exponent++;
		}
	}
	return (decimal);
}

// Parse t_ieee754_double to exponent and mantissa decimal
static void	parse_ieee754_double(t_ieee754_double *d, t_decimal *decimal,
		int *exponent)
{
	unsigned long long	mantissa;

	mantissa = d->ieee.mantissa;
	if (is_d_denormalized(*d))
	{
		*exponent = (1 - IEEE754_DOUBLE_BIAS) - IEEE754_DOUBLE_MANTISSA_BITS;
		*decimal = new_decimal(mantissa);
	}
	else
	{
		*exponent = (d->ieee.exponent - IEEE754_DOUBLE_BIAS)
			- IEEE754_DOUBLE_MANTISSA_BITS;
		mantissa += ((long long)1 << IEEE754_DOUBLE_MANTISSA_BITS);
		*decimal = new_decimal(mantissa);
	}
}

// Pad left side of res with 0
static	void	padzero(int pad, char *res)
{
	if (pad > 0)
		ft_memmove(res + pad, res, ft_strlen(res) + 1);
	while (pad > 0)
	{
		*res++ = '0';
		pad--;
	}
}

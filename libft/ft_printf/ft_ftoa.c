/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:26:29 by susami            #+#    #+#             */
/*   Updated: 2022/09/11 15:18:41 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_ieee754.h"
#include "ft_decimal.h"

void				ftoa(float f, char *res, int width, int precision);
static void			padzero(int pad, char *res);
static t_decimal	ieee754_float_to_decimal(t_ieee754_float *f);

/*
   Convert float value `f` to string `res`.
   `res` will be NULL terminated string.
   `width` is the total length of the result string.
   If result string is shorter than `width`, left side will be padded with 0.
   `precision` is the right side length not including dot.
   If `precision` is 0, then no dot will be added.

   The size of `res` must be >= max(FLT_MAX_INT + FLT_MAX_FRACT, width + 1).
*/
void	ftoa(float f, char *res, int width, int precision)
{
	t_ieee754_float	*ieee_f;
	t_decimal		decimal;

	ieee_f = (t_ieee754_float *)(&f);
	if (is_nan(*ieee_f))
	{
		ft_memmove(res, "nan", 4);
		return ;
	}
	if (is_negative(*ieee_f))
		*res++ = '-';
	if (is_inf(*ieee_f))
	{
		ft_memmove(res, "inf", 4);
		return ;
	}
	decimal = ieee754_float_to_decimal(ieee_f);
	decimal_to_str(decimal, res, precision);
	padzero(width - (int)ft_strlen(res), res);
}

// Convert number from ieee754_float to t_decimal without losing precision
static t_decimal	ieee754_float_to_decimal(t_ieee754_float *f)
{
	t_decimal	decimal;
	int			exponent;

	exponent = f->ieee.exponent - IEEE754_FLOAT_BIAS - 23;
	decimal = new_decimal((1 << 23) | f->ieee.mantissa);
	if (is_denormalized(*f))
	{
		exponent = (1 - IEEE754_FLOAT_BIAS) - 23;
		decimal = new_decimal(f->ieee.mantissa);
	}
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

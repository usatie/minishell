/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:57:00 by susami            #+#    #+#             */
/*   Updated: 2022/08/31 19:16:35 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ieee754.h"

bool	is_negative(t_ieee754_float f)
{
	return (f.ieee.negative == 1);
}

bool	is_inf(t_ieee754_float f)
{
	return (f.ieee.exponent == 0xff && f.ieee.mantissa == 0);
}

bool	is_nan(t_ieee754_float f)
{
	return (f.ieee.exponent == 0xff && f.ieee.mantissa > 0);
}

bool	is_denormalized(t_ieee754_float f)
{
	return (f.ieee.exponent == 0);
}

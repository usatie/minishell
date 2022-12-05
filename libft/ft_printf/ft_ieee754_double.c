/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:51:00 by susami            #+#    #+#             */
/*   Updated: 2022/09/02 16:54:13 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ieee754.h"

bool	is_d_negative(t_ieee754_double d)
{
	return (d.ieee.negative == 1);
}

bool	is_d_inf(t_ieee754_double d)
{
	return (d.ieee.exponent == 0x7ff && d.ieee.mantissa == 0);
}

bool	is_d_nan(t_ieee754_double d)
{
	return (d.ieee.exponent == 0x7ff && d.ieee.mantissa > 0);
}

bool	is_d_denormalized(t_ieee754_double d)
{
	return (d.ieee.exponent == 0);
}

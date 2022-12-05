/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ieee754.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:28:43 by susami            #+#    #+#             */
/*   Updated: 2022/09/02 18:28:10 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_IEEE754_H
# define FT_IEEE754_H

# include <stdbool.h>

/* Little endian. */
typedef union u_ieee754_float
{
	float	f;

	struct s_ieee754_float {
		unsigned int	mantissa:23;
		unsigned int	exponent:8;
		unsigned int	negative:1;
	}	ieee;
}	t_ieee754_float;

# define IEEE754_FLOAT_BIAS				0x7f /* Added to exponent.  */
# define IEEE754_FLOAT_MAX_EXP			0xff /* Max value of exponent bits.  */
# define IEEE754_FLOAT_MANTISSA_BITS	23 /* Number of mantissa bits.  */

/* Little endian. */
typedef union u_ieee754_double
{
	double	d;

	struct s_ieee754_double {
		unsigned long long	mantissa:52;
		unsigned int		exponent:11;
		unsigned int		negative:1;
	}	ieee;
}	t_ieee754_double;

# define IEEE754_DOUBLE_BIAS			0x3ff /* Added to exponent.  */
# define IEEE754_DOUBLE_MAX_EXP			0x7ff /* Max value of exponent bits.  */
# define IEEE754_DOUBLE_MANTISSA_BITS	52 /* Number of mantissa bits.  */

bool	is_negative(t_ieee754_float f);
bool	is_inf(t_ieee754_float f);
bool	is_nan(t_ieee754_float f);
bool	is_denormalized(t_ieee754_float f);

bool	is_d_negative(t_ieee754_double d);
bool	is_d_inf(t_ieee754_double d);
bool	is_d_nan(t_ieee754_double d);
bool	is_d_denormalized(t_ieee754_double d);
#endif /* ieee754.h */

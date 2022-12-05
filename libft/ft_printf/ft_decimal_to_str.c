/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:33:21 by susami            #+#    #+#             */
/*   Updated: 2022/09/14 21:35:00 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_decimal.h"

static bool			is_banker_round_down(t_decimal decimal, int precision);
static t_decimal	round_fract(t_decimal decimal, int precision);

/*
   Convert decimal to string.

   `res` will be NULL terminated string.
   `precision` is the right side length not including dot.
   If `precision` is 0, then no dot will be added.

   The size of `res` must be >= DOUBLE_MAX_FRACT + DOUBLE_MAX_INT.
*/
void	decimal_to_str(t_decimal decimal, char *res, int precision)
{
	int	i;

	decimal = round_fract(decimal, precision);
	i = 0;
	while (i < DOUBLE_MAX_INT - 1 && decimal.int_digits[i] == 0)
		i++;
	while (i < DOUBLE_MAX_INT)
		*res++ = decimal.int_digits[i++] + '0';
	if (precision > 0)
		*res++ = '.';
	i = 0;
	while (i < precision)
	{
		if (i < DOUBLE_MAX_FRACT)
			*res = decimal.fract_digits[i] + '0';
		else
			*res = '0';
		res++;
		i++;
	}
	*res = '\0';
}

/*
Banker round rounds to the nearest even integer.
0.25 -> 0.2
0.5 -> 0
0.75 -> 0.8

But this is applied only when precision == decimal.precision.
*/
static bool	is_banker_round_down(t_decimal decimal, int precision)
{
	char	next_digit;

	if (precision != decimal.precision)
		return (false);
	if (decimal.fract_digits[precision] != 5)
		return (false);
	if (precision > 0)
		next_digit = decimal.fract_digits[precision - 1];
	else
		next_digit = decimal.int_digits[DOUBLE_MAX_INT - 1];
	return (next_digit % 2 == 0);
}

/*
Round fractional part.
In a way to conform to IEEE754.
*/
static t_decimal	round_fract(t_decimal decimal, int precision)
{
	int	i;
	int	carry;

	if (precision >= DOUBLE_MAX_FRACT || decimal.fract_digits[precision] < 5)
		return (decimal);
	if (is_banker_round_down(decimal, precision))
		return (decimal);
	i = precision - 1;
	carry = 1;
	while (carry > 0 && i >= 0)
	{
		decimal.fract_digits[i] += carry;
		carry = decimal.fract_digits[i] / 10;
		decimal.fract_digits[i] %= 10;
		i--;
	}
	i = DOUBLE_MAX_INT - 1;
	while (carry > 0 && i >= 0)
	{
		decimal.int_digits[i] += carry;
		carry = decimal.int_digits[i] / 10;
		decimal.int_digits[i] %= 10;
		i--;
	}
	return (decimal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:06:03 by susami            #+#    #+#             */
/*   Updated: 2022/09/14 21:52:42 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_decimal.h"
#include "libft.h"

// Create decimal from num
t_decimal	new_decimal(unsigned long long num)
{
	t_decimal	decimal;
	size_t		i;

	ft_memset(&decimal, 0, sizeof(t_decimal));
	i = 0;
	while (i < DOUBLE_MAX_INT && num > 0)
	{
		decimal.int_digits[DOUBLE_MAX_INT - 1 - i] = num % 10;
		num /= 10;
		i++;
	}
	return (decimal);
}

// Multiply decimal value with int value
t_decimal	mul_decimal(t_decimal decimal, int n)
{
	int		i;
	char	carry;

	i = decimal.precision;
	carry = 0;
	while (i >= 0)
	{
		decimal.fract_digits[i] *= n;
		decimal.fract_digits[i] += carry;
		carry = decimal.fract_digits[i] / 10;
		decimal.fract_digits[i] %= 10;
		if (i == decimal.precision && decimal.fract_digits[i] == 0)
			decimal.precision--;
		i--;
	}
	i = DOUBLE_MAX_INT - 1;
	while (i >= 0)
	{
		decimal.int_digits[i] *= n;
		decimal.int_digits[i] += carry;
		carry = decimal.int_digits[i] / 10;
		decimal.int_digits[i] %= 10;
		i--;
	}
	return (decimal);
}

// Divide decimal value by int value
t_decimal	div_decimal(t_decimal decimal, int n)
{
	int		i;
	char	carry;

	carry = 0;
	i = 0;
	while (i < DOUBLE_MAX_INT)
	{
		carry *= 10;
		carry += decimal.int_digits[i];
		decimal.int_digits[i] = carry / n;
		carry %= n;
		i++;
	}
	i = 0;
	while (i < DOUBLE_MAX_FRACT)
	{
		carry *= 10;
		carry += decimal.fract_digits[i];
		decimal.fract_digits[i] = carry / n;
		if (decimal.fract_digits[i] != 0)
			decimal.precision = i;
		carry %= n;
		i++;
	}
	return (decimal);
}

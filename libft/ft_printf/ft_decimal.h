/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:03:51 by susami            #+#    #+#             */
/*   Updated: 2022/09/14 20:52:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DECIMAL_H
# define FT_DECIMAL_H

# define DOUBLE_MAX_INT 310
# define DOUBLE_MAX_FRACT 1075

// t_decimal can store a number in decimal format
typedef struct s_decimal {
	char	int_digits[DOUBLE_MAX_INT];
	char	fract_digits[DOUBLE_MAX_FRACT];
	int		precision;
}	t_decimal;

t_decimal	new_decimal(unsigned long long num);
t_decimal	mul_decimal(t_decimal decimal, int n);
t_decimal	div_decimal(t_decimal decimal, int n);
void		decimal_to_str(t_decimal decimal, char *res, int precision);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:49:06 by susami            #+#    #+#             */
/*   Updated: 2022/05/28 17:49:24 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_vprintf(const char *format, va_list ap)
{
	int		ret;

	ret = ft_vdprintf(STDOUT_FILENO, format, ap);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argparse_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:25:22 by susami            #+#    #+#             */
/*   Updated: 2022/06/01 18:00:48 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// exit()
#include <stdlib.h>
// STDERR_FILENO
#include <unistd.h>
// INT_MAX / INT_MIN
#include <limits.h>
// errno
#include <errno.h>
// ft_strtol()
#include "libft.h"
#include "ft_argparse.h"
#include "ft_printf.h"

static void	ap_fail(const char *fname, const char *msg, const char *arg,
				const char *var_name)	__attribute__((noreturn));

static void	ap_fail(const char *fname, const char *msg, const char *arg,
	const char *var_name)
{
	ft_dprintf(STDERR_FILENO, "%s error", fname);
	if (var_name != NULL)
		ft_dprintf(STDERR_FILENO, " (in %s)", var_name);
	ft_dprintf(STDERR_FILENO, ": %s\n", msg);
	if (arg != NULL && *arg != '\0')
		ft_dprintf(STDERR_FILENO, "		offending text: %s\n", arg);
	exit(EXIT_FAILURE);
}

static long	ap_num(const char *fname, const char *arg, int flags,
	const char *var_name)
{
	long	res;
	char	*endptr;
	int		base;

	if (arg == NULL || *arg == '\0')
		ap_fail(fname, "null or empty string", arg, var_name);
	if (flags & AP_ANY_BASE)
		base = 0;
	else if (flags & AP_BASE_8)
		base = 8;
	else if (flags & AP_BASE_16)
		base = 16;
	else
		base = 10;
	errno = 0;
	res = ft_strtol(arg, &endptr, base);
	if (errno != 0)
		ap_fail(fname, "ft_strtol() failed", arg, var_name);
	if (*endptr != '\0')
		ap_fail(fname, "nonnumeric characters", arg, var_name);
	if ((flags & AP_NONEG) && res < 0)
		ap_fail(fname, "value must be >= 0", arg, var_name);
	if ((flags & AP_GT_0) && res <= 0)
		ap_fail(fname, "value must be > 0", arg, var_name);
	return (res);
}

long	ft_argparse_long(const char *arg, int flags, const char *var_name)
{
	return (ap_num("get_long", arg, flags, var_name));
}

int	ft_argparse_int(const char *arg, int flags, const char *var_name)
{
	long	res;

	res = ap_num("get_int", arg, flags, var_name);
	if (res > INT_MAX || res < INT_MIN)
		ap_fail("get_int", "integer out of range", arg, var_name);
	return ((int)res);
}

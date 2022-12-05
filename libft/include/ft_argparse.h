/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argparse_num.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:22:07 by susami            #+#    #+#             */
/*   Updated: 2022/05/28 22:26:30 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARGPARSE_H
# define FT_ARGPARSE_H

# define AP_NONEG	01	/* Value must be >= 0 */
# define AP_GT_0	02	/* Value must be > 0 */

								/* By default, integers are decimal */
# define AP_ANY_BASE	0100	/* Can use any base - like strtol(3) */
# define AP_BASE_8		0200	/* Value is expressed in octal */
# define AP_BASE_16		0400	/* Value is expressed in hexadecimal */

long	ft_argparse_long(const char *arg, int flags, const char *var_name);
int		ft_argparse_int(const char *arg, int flags, const char *var_name);

#endif

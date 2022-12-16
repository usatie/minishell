/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:12:18 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 13:30:03 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termios.h>
#include "minishell.h"

void	setup_term(void)
{
	struct termios	tp;
	int				ttyfd;

	if (tcgetattr(STDIN_FILENO, &tp) == 0)
		ttyfd = STDIN_FILENO;
	else if (tcgetattr(STDOUT_FILENO, &tp) == 0)
		ttyfd = STDOUT_FILENO;
	else if (tcgetattr(STDERR_FILENO, &tp) == 0)
		ttyfd = STDERR_FILENO;
	else
		return ;
	tp.c_lflag &= ~ECHOCTL;
	tcsetattr(ttyfd, TCSAFLUSH, &tp);
}

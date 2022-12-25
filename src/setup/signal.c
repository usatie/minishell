/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:10:41 by susami            #+#    #+#             */
/*   Updated: 2022/12/25 21:58:19 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

static void	handler(int signum);
static void	setup_sigint(void);
static void	setup_sigquit(void);

void	setup_signal(void)
{
	setup_sigint();
	setup_sigquit();
}

static void	handler(int signum)
{
	g_env.sig = signum;
}

static void	setup_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(1);
}

static void	setup_sigquit(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = handler;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(SIGQUIT, &sa_ignore, NULL) < 0)
		exit(1);
}

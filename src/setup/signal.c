/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:10:41 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 11:10:06 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

static void	handler(int signum);
static void	setup_sigint(void);

void	setup_signal(void)
{
	setup_sigint();
	ignore_signal(SIGQUIT);
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

void	ignore_signal(int signum)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(signum, &sa_ignore, NULL) < 0)
		exit(1);
}

void	default_signal(int signum)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_DFL;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(signum, &sa_ignore, NULL) < 0)
		exit(1);
}

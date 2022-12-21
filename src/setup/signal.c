/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:10:41 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 11:39:22 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

static void	sigint_handler(int signum);
static void	setup_sigint(void);
static void	setup_sigquit(void);

void	setup_signal(void)
{
	setup_sigint();
	setup_sigquit();
}

static void	sigint_handler(int signum)
{
	g_env.sig = 1;
	(void)signum;
}

static void	setup_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(1);
}

static void	setup_sigquit(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(SIGQUIT, &sa_ignore, NULL) < 0)
		exit(1);
}

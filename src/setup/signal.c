/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:10:41 by susami            #+#    #+#             */
/*   Updated: 2022/12/20 13:55:32 by susami           ###   ########.fr       */
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

static int	check_state(void)
{
	t_pipeline	*pipeline;

	setup_term();
	pipeline = g_env.pipeline;
	if (pipeline)
	{
		while (pipeline)
		{
			if (pipeline->pid > 0)
				kill(pipeline->pid, SIGINT);
			pipeline = pipeline->next;
		}
	}
	else
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay(); // Refresh the prompt
	}
	return (0);
}

static void	sigint_handler(int signum)
{
	check_state();
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

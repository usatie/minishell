/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:10:41 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 13:55:27 by susami           ###   ########.fr       */
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
	t_pipeline	*pipeline;

	(void)signum;
	setup_term();
	pipeline = g_env.pipeline;
	if (pipeline)
	{
		while (pipeline)
		{
			kill(pipeline->pid, SIGINT);
			pipeline = pipeline->next;
		}
	}
	else
	{
		write(STDERR_FILENO, "\n", 1); // Move to a new line
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay(); // Refresh the prompt
	}
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

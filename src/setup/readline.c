/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:20:08 by susami            #+#    #+#             */
/*   Updated: 2022/12/20 12:32:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

/*
static int	check_state(void)
{
	t_pipeline	*pipeline;

	//printf("check_state: g_env.signal_handled = %d\n", g_env.signal_handled);
	if (!g_env.signal_handled)
		return (0);
	g_env.signal_handled = 0;
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
		//rl_done = 1;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay(); // Refresh the prompt
		g_env.interrupted = 1;
		close(STDIN_FILENO);
	}
	return (0);
}
*/

void	setup_rl(void)
{
	rl_outstream = stderr;
	//rl_signal_event_hook = check_state;
}

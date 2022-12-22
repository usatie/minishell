/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:20:08 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 16:30:12 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

static int	check_state(void);

void	setup_rl(void)
{
	rl_outstream = stderr;
	if (isatty(STDIN_FILENO))
		rl_event_hook = check_state;
}

static int	check_state(void)
{
	if (!g_env.sig)
		return (0);
	g_env.sig = 0;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay(); // Refresh the prompt
	return (0);
}

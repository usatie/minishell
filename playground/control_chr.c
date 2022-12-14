#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <readline/readline.h>
#include <termios.h>

void	handler(int sig) {
	(void)sig;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line(); // tell readline newline
	rl_replace_line("", 1); // clear current input
	rl_redisplay(); // refresh readline prompt
}

void setup_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(1);
}

void setup_sigquit(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		exit(1);
}

void setup_termios(void)
{
	struct termios	tp;
	if (tcgetattr(STDIN_FILENO, &tp) < 0)
		exit(1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) < 0)
		exit(1);
}

void setup_rl(void)
{
	rl_outstream = stderr;
}

int	main(void) {
	char	*line;

	setup_sigquit();
	setup_sigint();
	setup_termios();
	setup_rl();
	while (1)
	{
		line = readline("nanoshell$ ");
		if (!line)
		{
			write(STDERR_FILENO, "exit\n", 5);
			break ;
		}
	}
	return (0);
}

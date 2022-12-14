#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

#include <unistd.h>
#include <termios.h>

// gcc signal.c -lreadline

pid_t	childpid;

void	setup_rl(void)
{
	rl_outstream = stderr;
}

void	setup_term(void)
{
	struct termios tp;

	if (tcgetattr(STDIN_FILENO, &tp) == -1)
		exit(1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
		exit(1);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1); // Move to a new line
	rl_on_new_line(); // Regenerate the prompt on a newline
	rl_replace_line("", 0); // Clear the previous text
	rl_redisplay(); // Refresh the prompt
	setup_term();
}

void	setup_sigint(void)
{
	struct sigaction	sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(1);
}

void	setup_sigquit(void)
{
	struct sigaction	sa_ignore;
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigemptyset(&sa_ignore.sa_mask);
	if (sigaction(SIGQUIT, &sa_ignore, NULL) < 0)
		exit(1);
}

int	main(void)
{
	char	*line;

	setup_rl();
	setup_sigint();
	setup_sigquit();
	setup_term();
	while (1)
	{
		line = readline("nanoshell$ ");
		if (!line || strcmp("exit", line) == 0)
			break ;
		system(line);
	}
	write(STDERR_FILENO, "exit\n", 5);
	return (0);
}

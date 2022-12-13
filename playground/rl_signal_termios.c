#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
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

void	setup_signal(void)
{
	//signal(SIGINT, handler);
	struct sigaction	sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		exit(1);
}

int	main(void)
{
	char	*line;

	setup_rl();
	setup_signal();
	setup_term();
	while (1)
	{
		line = readline("nanoshell$ ");
		if (!line)
		{
			write(STDERR_FILENO, "exit", 4);
			exit(0);
		}
		system(line);
	}
	return (0);
}

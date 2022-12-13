#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

// gcc signal.c -lreadline

pid_t	childpid;

void	handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	char	*line;

	signal(SIGINT, handler);
	while (1)
	{
		line = readline("nanoshell$ ");
		system(line);
	}
	return (0);
}

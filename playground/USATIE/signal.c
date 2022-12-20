#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

//gcc -L $RL_PATH/lib -I $RL_PATH/include signal.c -lreadline

void handler(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	char *line;	

	signal(SIGINT, handler);
	while (1)
	{
		line = readline("nanoshell $ ");
		system(line);
	}
	return (0);
}

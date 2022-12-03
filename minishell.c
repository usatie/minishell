#include <errno.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT "minishell > "

int	main(void)
{
	char	*line;
	int		status;

	while (1)
	{
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		if (strcmp(line, "exit") == 0)
			exit(0);
		status = system(line);
		free(line);
	}
	return (status >> 8);
}

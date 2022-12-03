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

	while (1)
	{
		line = readline(PROMPT);
		if (line != NULL)
			system(line);
		else
			break ;
		free(line);
	}
}

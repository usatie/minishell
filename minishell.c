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

	line = readline(PROMPT);
	system(line);
	free(line);
}

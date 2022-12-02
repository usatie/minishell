#include <errno.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	*line;
	char	*prompt;

	prompt = "minishell > ";
	line = readline(prompt);
	printf("%s\n", line);
}

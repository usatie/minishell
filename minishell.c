#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell-0.1$ ");
		if (line && *line)
		{
			if (strcmp(line, "exit") == 0)
				exit(0);
			printf("%s\n", line);
		}
	}
	return (0);
}

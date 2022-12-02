#include <readline/readline.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char	*envp[];

void	exec_cmd(const char *line)
{
	system(line);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell-0.1$ ");
		if (line == NULL)
			break ;
		if (*line)
		{
			if (strcmp(line, "exit") == 0)
				exit(0);
			exec_cmd(line);
		}
	}
	return (0);
}

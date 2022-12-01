#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell-0.1$ ");
		printf("%s\n", line);
	}
	return (0);
}

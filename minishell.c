#include <stdio.h>
#include <readline/readline.h>

int main()
{
    char *line;
    
    while (1)
    {
        line = readline("minishell $ ");
        printf("%s\n", line);
    }
    return 0;
}

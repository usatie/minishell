#include <stdio.h>
#include <readline/readline.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *line;
    
    while (1)
    {
        line = readline("minishell $ ");
        if (line && *line) // why
        if (line == NULL) 
            break;
        if (*line)
        {
            if (strcmp(line, "exit") == 0)
                exit(0);
            printf("%s\n", line);
        }
    }
    return 0;
}

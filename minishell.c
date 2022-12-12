#include <stdio.h>
#include <readline/readline.h>
#include <string.h>
#include <stdlib.h>


extern char     *envp[];

void    exec_cmd(const char *line)
{
    system(line);
}

int main()
{
    char *line;
    
    while (1)
    {
        line = readline("minishell $ ");
        if (line == NULL) 
            break;
        if (*line)
        {
            if (strcmp(line, "exit") == 0)
                exit(0);
//           printf("%s\n", line);
            exec_cmd(line);
       }
    }
    return 0;
}

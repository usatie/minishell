#include <stdio.h>
#include <readline/readline.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

extern char     *envp[];

#define NUM_BUILTIN 7

bool is_builtin(const char *cmd)
{
    const char *cmds[NUM_BUILTIN] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int i = 0;

    while (i < NUM_BUILTIN)
    {
        if (strcmp(cmd, cmds[i]) == 0)
            return (true);
        i++;
    }
    return (false);
}

void exec_builtin(const char *line)
{
    if (strcmp(line, "exit") == 0)
        exit(0);
    // TODO:echo
    // TODO:cd
    // TODO:pwd
    // TODO:export
    // TODO:unset
    // TODO:env
    system(line);
}

void exec_non_builtin(const char *line)
{
    system(line);
}

void exec(const char *line)
{
    if (is_builtin(line))
        exec_builtin(line);
    else
        exec_non_builtin(line);
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
            exec(line);
    }
    return 0;
}

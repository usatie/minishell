# include <stdio.h>
# include <readline/readline.h>
int main(void)
{
    char *hoge;
    char *line;

    hoge = "minishell $ ";
    line = readline(hoge);
    printf("%s\n", line);
}


#include <string.h>
#include <stdio.h>

char *strtok(char *s1, const char *s2)
{
    char *pbegin, *pend;
    static char *save = "";

    pbegin = s1 ? s1 : save;
    pbegin += strspn(pbegin, s2);
    if (*pbegin == '\0'){
        save = "";
        return NULL;
    }

    pend = pbegin + strcspn(pbegin, s2);
    if (*pend != '\0')
        *pend++ = '\0';
    save = pend;

    return pbegin;
}



int main()
{
    char s1[50] = "cat MAkefile | grep minishell";
    char s2[50] = "|&;()<> ";

    char *p = strtok(s1,s2);

    puts(p);
    
    while (p!=NULL){
        p = strtok(NULL, s2);

        if (p != NULL){
            puts(p);
        }
    }
    return 0;
}

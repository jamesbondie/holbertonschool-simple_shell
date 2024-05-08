#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
        char *args[] = {"/bin/ls", NULL};
        if(isatty(0) && ac > 0)
        {
                printf("asdf");
        }
        else
        {
                if(execve(args[0], args, environ) == -1)
                        perror(av[0]);
        }
        return 0;
}

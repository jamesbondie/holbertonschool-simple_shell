#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
        char *args[65];
        if(isatty(0) && ac > 0)
        {
                printf("asdfsdf");
        }
        else
        {
                if (execve("/bin/ls", args, environ) == -1)
                {
                        fprintf(stderr, "%s: 1: not found\n", av[0]);
                        exit(90);
                }
        }
        return(60);
}

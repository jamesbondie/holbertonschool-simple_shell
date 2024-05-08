#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
        char *args[65];
        if(isatty(0) && ac > 0)
        {
                fprintf(stderr, "adsf");
        }
        else
        {
                args[0] = "/bin/ls";
                if (execve(args[0], args, environ) == -1)
                        perror(av[0]);
                }
                return 0;
}

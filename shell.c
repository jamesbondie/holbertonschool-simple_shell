#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
        char *args[] = { "ls", NULL, NULL, NULL, NULL};
        if(isatty(0) && ac > 0)
        {
                fprintf(stderr, "adsf");
        }
        else
        {
                if (execve("/bin/ls", args, environ) == -1)
                        perror(av[0]);
                }
                return 0;
}

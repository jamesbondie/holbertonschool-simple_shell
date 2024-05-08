#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
        size_t bufsize = 5;
        char *buffer = malloc(sizeof(char) * bufsize);
        char *args[65];
        if(isatty(0) && ac > 0)
        {
                fprintf(stderr, "adsf");
        }
        else
        {
                if (getline(&buffer,&bufsize,stdin) == -1)
                        free(buffer);
                if (buffer[strlen(buffer) - 1] == '\n')
                        buffer[strlen(buffer) - 1] = '\0';
                
                if (execve(buffer, args, environ) == -1)
                        perror(av[0]);
        }
                return 0;
}

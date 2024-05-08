#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
        char *buffer;
        size_t bufsize = 5;
        pid_t my_pid;
        int blabla;
        char *args[] = { "bin", "-c", NULL};
        buffer = malloc(bufsize*sizeof(char));
        if(isatty(0) && ac > 0)
        {
                while (1)
                {
                        printf("#cisfun$ ");
                        if (getline(&buffer,&bufsize,stdin) == -1)
                                free(buffer);
                        if (buffer[strlen(buffer) - 1] == '\n')
                                buffer[strlen(buffer) - 1] = '\0';
                        my_pid = fork();
                        if (my_pid != 0)
                                wait(&blabla);
                        if (my_pid == 0)
                        {
                                if (execve(buffer, args, NULL) == -1)
                                        perror(av[0]);
                        }
                }
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
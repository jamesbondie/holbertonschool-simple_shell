#include "main.h"
extern char** environ;

int main (int ac, char **av)
{
    pid_t my_pid;
    int status;
    char *args[2];

    args[0] = "/bin/ls";
    args[1] = NULL;

    if(isatty(0) && ac > 0)
    {
            printf("asdfsdf");
    }
    else
    {
        my_pid = fork();
        if (my_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (my_pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                fprintf(stderr, "%s: 1: not found\n", av[0]);
                exit(EXIT_FAILURE);
            }
        }
        else 
        {
            wait(&status);
            if (WIFEXITED(status))
            {
                return WEXITSTATUS(status);
            }
        }
    }
    return 0;
}
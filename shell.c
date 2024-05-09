#include "main.h"
extern char** environ;
int main (int ac, char **av)
{
    pid_t my_pid;
    size_t bufsize = 3;
    int status;
    char *args[64];
    char *buffer = malloc(bufsize * sizeof(char));
    char *token;    
    int i = 0;
    
    if (!buffer)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    args[0] = NULL;
    args[1] = NULL;

    if(isatty(0) && ac > 0)
    {
            printf("asdfsdf");
    }
    else
    { 
        while (getline(&buffer, &bufsize, stdin) != -1)
        {
            i = 0;
            if (buffer[strlen(buffer) - 1] == '\n')
                buffer[strlen(buffer) - 1] = '\0';
            
            token = strtok(buffer, " \n");
            while (token != NULL)
            {
                    args[i] = token;
                    token = strtok(NULL, " \n");
                    i++;  
            }
            args[i] = NULL;   
            my_pid = fork();
            if (my_pid == -1)
            {
                perror("fork");
                exit(EXIT_FAILURE);
                
            }
            else if (my_pid == 0)
            {
                if (strchr(args[0], '/') != 0)
                {
                    if (execve(args[0], args, environ) == -1)
                    {
                        fprintf(stderr, "%s: 1: %s: not found\n", av[0], buffer);
                        free(buffer);
                        exit(EXIT_FAILURE);
                    }
                }
            }
                
            else 
            {
                wait(&status); 
            }
        }
    }
    free(buffer);
    return 0;
}
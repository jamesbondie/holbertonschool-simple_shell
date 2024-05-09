#include "main.h"
extern char** environ;
void space_remover(char *str)
{
        int i = 0;
        int j = 0;
        int len = strlen(str);
        for (i = j = 0; i < len; i++)
        {
                if (str[i] != ' ')
                    str[j++] = str[i];
        }
        str[j] = '\0';
}
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
            space_remover(token);
            while (token != NULL)
            {
                    args[i] = token;
                    token = strtok(NULL, " \n");
                    space_remover(token);
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
                if (execve(args[0], args, environ) == -1)
                {
                    fprintf(stderr, "%s: 1: %s: not found\n", av[0], buffer);
                    free(buffer);
                    exit(EXIT_FAILURE);
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
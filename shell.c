#include "main.h"
int interactive(char *buffer, size_t bufsize, char **args, char *av)
{
        char *token;
        pid_t my_pid;
        int i = 0, status, j;
        while (getline(&buffer, &bufsize, stdin) != -1)
        {
                i = 0;
                if (buffer[strlen(buffer) - 1] == '\n')
                        buffer[strlen(buffer) - 1] = '\0';
                token = strtok(buffer, " \n");
                if (token == NULL)
                {
                        free(buffer);
                        exit(EXIT_SUCCESS);
                }
                while (token != NULL)
                {
                        args[i] = strdup(token);
                        if (!args[i])
                        {
                                perror("strdup");
                                exit(EXIT_FAILURE);
                        }
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
                        if (execve(args[0], args, environ) == -1)
                        {
                                fprintf(stderr, "%s: 1: %s: not found\n", av, buffer);
                                free(buffer);
                                for (j = 0; j < i; j++)
                                        free(args[j]);
                                exit(EXIT_FAILURE);
                        }
                }
                else
                        wait(&status);
        }
        return (i);
}

int main(int ac, char **av)
{
        size_t bufsize = 3;
        int b = 0, j;
        char *args[64], *buffer = malloc(bufsize * sizeof(char));
        if (!buffer)
        {
                perror("malloc");
                exit(EXIT_FAILURE);
        }
        args[0] = NULL, args[1] = NULL;
        if (isatty(0) && ac > 0)
                printf("asdfsdf");
        else
        {
                b = interactive(buffer, bufsize, args, av[0]);
        }
        for (j = 0; j < b; j++)
                free(args[j]);
        free(buffer);
        return (0);
}
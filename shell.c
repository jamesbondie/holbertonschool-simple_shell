#include "main.h"
void _getenv(const char* name, char *args[64])
{
    extern char** environ;
    int j = 0;
    size_t i;

    for (i = 0; environ[i] != NULL; i++)
    {
        char* env_var = strdup(environ[i]);
        char* token = strtok(env_var, "=");

        if (token != NULL && strcmp(token, name) == 0)
        {
            token = strtok(NULL, ":");

            while (token != NULL)
            {
                args[j] = strdup(token), j++;
                token = strtok(NULL, ":");
            }
            args[j] = NULL;
            break;
        }
        free(env_var);
    }
}

void args_yazan(char *arv[64], char *kod_tutan)
{
    char *args[64];
    char* nese = strdup(kod_tutan);
    int i = 0, j = 0;
        _getenv("PATH", args);
    while (args[i])
    {
        strcat(args[i], "/");
        strcat(args[i], nese);
        if (access(args[i], X_OK) == 0)
        {
            arv[j] = strdup(args[i]);
            break;
            j++;
        }
        i++;
    }
    free(nese);
}
int main(int ac, char **av)
{
        pid_t my_pid;
        size_t bufsize = 3;
        int status;
        char *args[64];
        char *buffer = malloc(bufsize * sizeof(char));
        char *token;
        int i = 0, j;
        if (!buffer)
        {
                perror("malloc");
                exit(EXIT_FAILURE);
        }
        args[0] = NULL;
        args[1] = NULL;
        if (isatty(0) && ac > 0)
                printf("asdfsdf");
        else
        {
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
                                if (strchr(args[0], '/') == 0)
                                {
                                        args_yazan(args, args[0]);
                                }
                                if (execve(args[0], args, environ) == -1)
                                {
                                        fprintf(stderr, "%s: 1: %s: not found\n", av[0], buffer);
                                        free(buffer);
                                        for (j = 0; j < i; j++)
                                        free(args[j]);
                                        exit(EXIT_FAILURE);
                                }
                        }
                        else
                        wait(&status);
                        for (j = 0; j < i; j++)
                        free(args[j]);
                }
        }
        free(buffer);
        return (0);
}
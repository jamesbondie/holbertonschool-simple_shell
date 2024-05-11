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

void _printenv(char **envi)
{
        int i = 0;
        while(envi[i] != NULL)
                {
                        printf("%s\n", envi[i]);
                        i++;
                }
}



void args_writer(char *arv[64], char *code_holder)
{
    char *args[64];
    char *nese = strdup(code_holder);
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
        size_t bufsize = 64;
        int status, status_tutan = 5;
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
                {
                        while (1)
                        {       i = 0;
                                printf("$ ");
                                if (getline(&buffer, &bufsize, stdin) != -1)
                                {
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
                                                        free(buffer);
                                                        exit(EXIT_FAILURE);
                                                }
                                                token = strtok(NULL, " \n");
                                                i++;

                                        }
                                        args[i] = NULL;

                                        if (strcmp(args[0], "exit") == 0)
                                                break;
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
                                                        args_writer(args, args[0]);
                                                }
                                                for (j = 1; j < i; j++)
                                                {
                                                        if (strchr(args[j], '.') != 0)
                                                        {
                                                                printf("asdfasf\n");
                                                        }
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
                                        {
                                        wait(&status);
                                        }
                                        for (j = 0; j < i; j++)
                                                free(args[j]);
                                                                }
                                else
                                        break;
                        }
                }

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
                        if (strcmp(args[0], "exit") == 0)
                        {
                                free(buffer);
                                for (j = 0; j < i; j++)
                                        free(args[j]);
                                if (status_tutan == 5)
                                        exit(0);
                                else if (status_tutan == 512)
                                        exit(2);
                        }
                        if (strcmp(args[0], "env") == 0)
                        {        
                                
                                free(buffer);
                                for(j = 0; j < i; j++)
                                        free(args[j]);
                                
                                _printenv(environ);
                                exit(EXIT_SUCCESS);
                                
                        }
                       if (strchr(args[0], '/') == 0)
                        {
                                args_writer(args, args[0]);
                        }
                        if (access(args[0], X_OK) != 0)
                                exit(127);
                        my_pid = fork();
                        if (my_pid == -1)
                        {
                                perror("fork");
                                exit(EXIT_FAILURE);
                        }
                        else if (my_pid == 0)
                        {
                                for (j = 1; j < i; j++)
                                {
                                        if (strchr(args[j], '.') != 0)
                                                exit(127);
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
                        status_tutan = status;
                        for (j = 0; j < i; j++)
                        free(args[j]);
                }
        }
        free(buffer);
        return (0);
}

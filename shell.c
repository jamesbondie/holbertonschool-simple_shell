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
            j++;
            break;
        }
        i++;
    }
    free(nese);
}

char execute_command(char *args[64], char *av[])
{
    pid_t my_pid;
    int status;
    extern char **environ;
    int status_tutan = 5;

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
        if (execve(args[0], args, environ) == -1)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
            
            exit(127);
        }
    }
    else
    {
        wait(&status);
        status_tutan = status;
    }
    
    if (status_tutan == 32512)
    {
        exit(127);
        return (127);
    }
    return 0;
}

void handle_exit(char *buffer, char *args[64], int ac, char *av[])
{
    int j;
    (void)ac;
    (void)av;
    free(buffer);
    for (j = 0; args[j] != NULL; j++)
        free(args[j]);
    exit(0);
}

void handle_env(char *buffer, char *args[64], int ac, char *av[])
{
    extern char **environ;
    int j;
    (void)ac;
    (void)av;
    free(buffer);
    for(j = 0; args[j] != NULL; j++)
        free(args[j]);

    _printenv(environ);
    exit(EXIT_SUCCESS);
}

void process_input(char *buffer, int ac, char *av[])
{
    extern char **environ;
    char *args[64];
    char *token;
    int i = 0, j;
    (void)ac;
    (void)av;
    args[0] = NULL;
    args[1] = NULL;
    i = 0;
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    token = strtok(buffer, " \n");
    if (token == NULL)
    {
        handle_exit(buffer, args, ac, av);
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
        handle_exit(buffer, args, ac, av);
    }
    if (strcmp(args[0], "env") == 0)
    {
        handle_env(buffer, args, ac, av);
    }
    execute_command(args, av);
    

    for (j = 0; args[j] != NULL; j++)
        free(args[j]);
}


int main(int argc, char **argv)
{
    size_t bufsize = 64;
    int status_tutan = 5;
    char *buffer = malloc(bufsize * sizeof(char));

    if (!buffer)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (getline(&buffer, &bufsize, stdin) != -1 && argc > 0)
    {
        process_input(buffer, argc, argv);
        if (status_tutan == 32512)
            return(127);
    }

    free(buffer);

    if (status_tutan == 32512)
        return 127;

    return 0;
}
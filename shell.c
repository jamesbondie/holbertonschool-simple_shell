#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void cleanup_args(char *args[]) {
    int i;
    for (i = 0; args[i] != NULL; i++) {
        free(args[i]);
    }
}

void _getenv(const char *name, char *args[]) {
    extern char **environ;
    int j = 0;
    size_t i;
    for (i = 0; environ[i] != NULL; i++) {
        char *env_var = strdup(environ[i]);
        char *token = strtok(env_var, "=");

        if (token != NULL && strcmp(token, name) == 0) {
            token = strtok(NULL, ":");

            while (token != NULL) {
                args[j] = strdup(token);
                if (args[j] == NULL) {
                    perror("strdup");
                    exit(EXIT_FAILURE);
                }
                j++;
                token = strtok(NULL, ":");
            }
            args[j] = NULL;
            break;
        }
        free(env_var);
    }
}

void _printenv(char *envi[]) {
    int i;
    for (i = 0; envi[i] != NULL; i++) {
        printf("%s\n", envi[i]);
    }
}

void args_writer(char *arv[], char *code_holder) {
    char *args[64] = {NULL};
    char *nese = strdup(code_holder);
    int i;
    _getenv("PATH", args);
    for (i = 0; args[i] != NULL; i++) {
        if (strlen(args[i]) + strlen(nese) + 2 <= 64) {
            strcat(args[i], "/");
            strcat(args[i], nese);
            if (access(args[i], X_OK) == 0) {
                arv[0] = strdup(args[i]);
                if (arv[0] == NULL) {
                    perror("strdup");
                    exit(EXIT_FAILURE);
                }
                break;
            }
        }
    }
    free(nese);
}


char execute_command(char *args[], char *av[]) {
    pid_t my_pid;
    int status;
    extern char **environ;
    int status_tutan = 5;

    my_pid = fork();
    if (my_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (my_pid == 0) {
        if (strchr(args[0], '/') == 0) {
            args_writer(args, args[0]);
        }
        if (execve(args[0], args, environ) == -1) {
            fprintf(stderr, "%s: 1: %s: not found\n", av[0], args[0]);
            exit(127);
        }
    } else {
        wait(&status);
        status_tutan = status;
    }

    if (status_tutan == 32512) {
        exit(127);
    }
    return 0;
}

void handle_exit(char *buffer, char *args[]) {
    free(buffer);
    cleanup_args(args);
    exit(0);
}

void handle_env(char *buffer, char *args[]) {
    extern char **environ;
    free(buffer);
    cleanup_args(args);
    _printenv(environ);
    exit(EXIT_SUCCESS);
}

void process_input(char *buffer, char *av[]) {
    char *args[64] = {NULL};
    char *token;
    int i = 0;

    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
    token = strtok(buffer, " \n");
    if (token == NULL) {
        handle_exit(buffer, args);
    }
    while (token != NULL) {
        args[i] = strdup(token);
        if (args[i] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        token = strtok(NULL, " \n");
        i++;
    }
    if (strcmp(args[0], "exit") == 0) {
        handle_exit(buffer, args);
    }
    if (strcmp(args[0], "env") == 0) {
        handle_env(buffer, args);
    }
    execute_command(args, av);
    cleanup_args(args);
}

int main(int argc, char **argv) {
    size_t bufsize = 64;
    char *buffer = malloc(bufsize * sizeof(char));
    int status_tutan;

    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    status_tutan = 5;

    while (getline(&buffer, &bufsize, stdin) != -1 && argc > 0) {
        process_input(buffer, argv);
    }

    free(buffer);
    if (status_tutan == 32512) {
        return 127;
    }

    return 0;
}

#include "main.h"

void _getenv(const char* name, char* args[64]) {
    extern char** environ;
    int j = 0;
    size_t i;
    for (i = 0; environ[i] != NULL; i++) {
        char* env_var = strdup(environ[i]);
        char* token = strtok(env_var, "=");
        if (token != NULL && strcmp(token, name) == 0) {
            token = strtok(NULL, ":");
            while (token != NULL) {
                args[j] = strdup(token);
                j++;
                token = strtok(NULL, ":");
            }
            args[j] = NULL;
            break;
        }
        free(env_var);
    }
}

void _printenv(char** envi) {
    int i = 0;
    while (envi[i] != NULL) {
        printf("%s\n", envi[i]);
        i++;
    }
}

int args_writer(char* arv[64], const char* code_holder) {
    char* argu[64];
    int i = 0, j = 0;
    _getenv("PATH", argu);
    while (argu[i]) {
        size_t len = strlen(argu[i]) + strlen(code_holder) + 2;
        char* path = malloc(len);
        if (!path) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        snprintf(path, len, "%s/%s", argu[i], code_holder);
        if (access(path, X_OK) == 0) {
            arv[j] = path;
            j++;
            break;
        }
        free(path);
        i++;
    }
    return 1;
}

int main(int argc, char* argv[]) {
    extern char **environ;
    char* buffer = NULL;
    size_t bufsize = 0;
    int j;
    int i;
    pid_t my_pid;
    char *args[64] = {NULL};
    char *token;
    if (argc < 0)
        exit(EXIT_SUCCESS);

    while (getline(&buffer, &bufsize, stdin) != -1) {
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        token = strtok(buffer, " \n");
        i = 0;
        while (token != NULL) {
            args[i] = strdup(token);
            if (!args[i]) {
                perror("strdup");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " \n");
            i++;
        }

        if (strcmp(args[0], "exit") == 0) {
            free(buffer);
            for (j = 0; j < i; j++)
                free(args[j]);
            exit(0);
        }

        if (strcmp(args[0], "env") == 0) {
            free(buffer);
            for (j = 0; j < i; j++)
                free(args[j]);
            _printenv(environ);
            exit(EXIT_SUCCESS);
        }

        if (strchr(args[0], '/') == NULL) {
            args_writer(args, args[0]);
        }

        my_pid = fork();
        if (my_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (my_pid == 0) {
            if (execve(args[0], args, environ) == -1) {
                fprintf(stderr, "%s: %s: not found\n", argv[0], args[0]);
                exit(EXIT_FAILURE);
            }
        } else {
            wait(NULL);
        }

        for (j = 0; args[j] != NULL; j++)
            free(args[j]);
    }

    free(buffer);
    return 0;
}

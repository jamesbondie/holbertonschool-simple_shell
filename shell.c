#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t line_size;
    int arg_count;
    pid_t pid;
    char *token;
    int status;
    char *args[65]; 
    if (isatty(0) && argc > 0) {
        while (1) {
            printf("#cisfun$ ");
            line_size = getline(&buffer, &bufsize, stdin);
            if (line_size == -1) {
                free(buffer); 
                if (feof(stdin)) {
                    printf("\n");
                    break;  
                } else {
                    perror("getline");
                    exit(EXIT_FAILURE);
                }
            }

            
            if (buffer[line_size - 1] == '\n')
                buffer[line_size - 1] = '\0';

            arg_count = 0;

            token = strtok(buffer, " ");
            while (token != NULL && arg_count < 64) {
                args[arg_count++] = token;
                token = strtok(NULL, " ");
            }
            args[arg_count] = NULL; 

           
            pid = fork();
            if (pid < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
            
                if (execvp(args[0], args) == -1) {
                    perror(argv[0]); 
                    exit(EXIT_FAILURE);
                }
            } else {
                wait(&status);
            }
        }
    } else {
        line_size = getline(&buffer, &bufsize, stdin);
        if (line_size == -1) {
            free(buffer); 
            perror("getline");
            exit(EXIT_FAILURE);
        }
        if (buffer[line_size - 1] == '\n')
            buffer[line_size - 1] = '\0';

        arg_count = 0;

        token = strtok(buffer, " ");
        while (token != NULL && arg_count < 64) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        
        if (execvp(args[0], args) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    free(buffer);
    exit(EXIT_SUCCESS);
}

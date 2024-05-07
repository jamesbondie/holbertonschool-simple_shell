#include "main.h"

int main (int ac, char **av)

{
        char *buffer;
        size_t bufsize = 5;
        pid_t my_pid;
        int blabla;
        buffer = malloc(bufsize*sizeof(char));
        int a = 0;
        int *x;
        x = &a;i
        while (a = 75)
        {
                my_pid = fork();

                if (my_pid != 0)
                        wait(&blabla);
                if (my_pid == 0)
                {
                        printf("#cisfun$ ");
                        getline(&buffer,&bufsize,stdin);
                        if (strcmp(buffer, "exit") == 0)
                                *x = a;
                        if (buffer[strlen(buffer) - 1] == '\n')
                                buffer[strlen(buffer) - 1] = '\0';
                        char* const newenvironment[] = {NULL};
                        char *args[] = { "mini_shell", buffer, NULL };
                        if (strcmp(
                        execve(buffer, av, newenvironment);
                }
        }
}

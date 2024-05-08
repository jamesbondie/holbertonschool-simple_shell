#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av, char **env)
{
    if (isatty(STDIN_FILENO)) {
        char *argv[] = {"/bin/sh", "-c", "env", 0};
	printf("%s, %d", av[0], ac);
        execve(argv[0], &argv[0], env);
        fprintf(stderr, "Oops!\n");
        return -1;
    } else {
        fprintf(stderr, "Not connected to a terminal!\n");
        return -1;
    }
}

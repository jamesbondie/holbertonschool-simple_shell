#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *argv[] = { "ls", NULL };
    char *envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "TZ=UTC0",
        "USER=beelzebub",
        "LOGNAME=tarzan",
        NULL
    };

    if (isatty(STDIN_FILENO))
    {
        fprintf(stderr, "Connected to a terminal\n");
    }
    else
    {
        execve("/bin/sh", argv, envp);
        perror("execve"); 
        return -1;
    }

    return 0;
}

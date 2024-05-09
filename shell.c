#include "main.h"
extern char** environ;
int main (void)
{
        if(isatty(0))
        {
                printf("asdfsdf");
        }
        else
        {
                printf("ashdfsfd");
        }
        return(60);
}

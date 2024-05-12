#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;
int args_writer(char *arv[64], char *code_holder);
void _printenv(char **envi);
int custom_getenv(const char *name, char *args[64]);

#endif

#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
void remove_spaces(char *str);
extern char **environ;
void process_input(char *buffer, int ac, char *av[]);
void handle_env(char *buffer, char *args[64], int ac, char *av[]);
void handle_exit(char *buffer, char *args[64], int ac, char *av[]);
char execute_command(char *args[64], char *av[]);
int args_writer(char *arv[64], char *code_holder);
void _printenv(char **envi);
void _getenv(const char *name, char *args[64]);
void cleanup_args(char *args[64]);

#endif

# C - Simple Shell Group Work


## FILES


### [README.md0-binary_tree_node.c](./README.md) 
* Info about Simple Shell Repository
### [AUTHORS](./AUTHORS) 
* Authors & Contributors of Simple Shell Repository
### [main.h](./main.h) 
* Headers and Prototypes of Simple Shell Programme 
### [shell.c](./shell.c) 
* Main Programme for Simple Shell
### [man_1_simple_shell](./man_1_simple_shell) 
* Manual page of Simple Shell



## Flowchart

<p align="center"><img src="https://github.com/jamesbondie"></p>


## SHELL
This project is a mini shell implementation which is a command language interpreter that shall execute commands read from a command line string, the standard in both interactive mode and non-interactive mode.  It provides basic command-line interface functionalities such as executing commands, handling environment variables, and displaying environment variables. 

## ABOUT

### Command Execution
* Executes commands entered by the user.

### Environment Variable Handling
* Provides functions to retrieve and print environment variables.

### Built-in Commands
* Includes built-in commands such as exit to terminate the shell and env to display environment variables.

## Features

### Dynamic Path Resolution
* One notable feature of the shell is its dynamic path resolution mechanism. When a command is entered without an absolute path, the shell searches through the directories listed in the PATH environment variable to find the executable file. This allows for seamless execution of commands without specifying their full paths.

### Error Handling
* The shell includes robust error handling mechanisms to gracefully handle various scenarios, such as command not found, memory allocation errors, and fork failures. Error messages are informative and help users understand the nature of the issue encountered.

### Clean Input Parsing
* Input parsing in the shell is handled efficiently and cleanly. User input is tokenized to separate commands and arguments, ensuring accurate execution and preventing common input-related errors.

### Process Management
* The shell effectively manages child processes spawned to execute commands. It utilizes the fork system call to create child processes, waits for their completion using the wait system call, and maintains proper handling of process statuses and exit codes.

### Compilation

Your code will be compiled this way:

```
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

```

### Usage

Your code will be run this way:

```
$ ./hsh

```



## Authors
*	Tahir Alizade - [Github]https://github.com/jamesbondie/
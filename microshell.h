#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdbool.h>
#define BUFFER_SIZE 200

ssize_t ft_putstr_endl(char* str, int fd);
ssize_t ft_putstr(char* str, int fd);
void fatal_error();
void exec_pipe(char* argv[], int len_argv, int tmpfd, char *const envp[]);

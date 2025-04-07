#include "microshell.h"

void fatal_error() {
		ft_putstr_endl("error: fatal", STDERR_FILENO);
		exit(EXIT_FAILURE);
}

int ft_strlen(char* str) {
		if (!str)
				return 0;
		int count = 0;
		while (*str++)
				count++;
		return count;
}

ssize_t ft_putstr(char* str, int fd) {
		if (!str)
				return 0;
		return write(fd, str, ft_strlen(str));
}

ssize_t ft_putstr_endl(char* str, int fd) {
		if (!str)
				return 0;
		int w = write(fd, str, ft_strlen(str));
		return w + write(fd, "\n", 1);
}

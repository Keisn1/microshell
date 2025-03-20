#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 200

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

int main(int argc, char* argv[], char *const envp[]) {
	if (argc < 2)
		return 0;	

	if(execve(argv[1], argv, envp) == -1) {
			ft_putstr("error: cannot execute ", STDERR_FILENO);
			ft_putstr_endl(argv[1], STDERR_FILENO);
	};
	return 0;
}

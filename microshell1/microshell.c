#include <unistd.h>

void err(char* str) {
	while (*str) 
		write(STDERR_FILENO, *str, 1);
}

void error_exec() {
	write(STDERR_FILENO, "error: cannot execute non-executable\n", 36);
}

int main(int argc, char* argv[], char* envp[]) {
	(void)argc;
	(void)argv;
	(void)envp;
	err("error: cannot execute non-executable"), err("\n");
}

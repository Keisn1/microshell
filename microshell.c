#include "microshell.h"

void ft_execve(char* argv[], int fd, char *const envp[]) {
		if (dup2(fd, STDIN_FILENO) == -1)
				fatal_error();
		if (close(fd) == -1)
				fatal_error();
		if(execve(argv[0], argv, envp) == -1) {
				ft_putstr("error: cannot execute ", STDERR_FILENO);
				ft_putstr_endl(argv[0], STDERR_FILENO);
				exit(1);
		};
}

void exec_pipe(char* argv[], int len_argv, int tmpfd, char *const envp[]) {
		int count = 0;

		int cmd_idx = 0;
		while (count < len_argv)  {
				if(argv[count][0] == '|') {
						argv[count] = NULL; 
						int pipefd[2];
						if (pipe(pipefd) == -1)
								fatal_error();

						pid_t pid = fork();
						if (pid == -1)
								fatal_error();
						if (pid == 0) {
								if (dup2(pipefd[1], STDOUT_FILENO) == -1)
										fatal_error();
								if (close(pipefd[1]) == -1)
										fatal_error();
								if (close(pipefd[0]) == -1)
										fatal_error();
								if (strcmp(argv[cmd_idx], "cd") == 0)  {
										if ((count - cmd_idx) == 2) {
												if(chdir(argv[cmd_idx+1]) == -1) {
														ft_putstr("error: cd: cannot change directory to ", STDERR_FILENO);
														ft_putstr_endl(argv[cmd_idx+1], STDERR_FILENO);
												}
										} else 
												ft_putstr_endl("error: cd: bad arguments", STDERR_FILENO);
										exit(EXIT_SUCCESS);
								} else
										ft_execve(argv+cmd_idx, tmpfd, envp);
						}
						cmd_idx = count + 1;
						if (close(pipefd[1]) == -1)
								fatal_error();
						if (close(tmpfd) == -1)
								fatal_error();
						tmpfd = pipefd[0];
				}
				count++;
		}
		pid_t pid = fork();
		if (pid == -1)
				fatal_error();
		if (pid == 0)  {
				if (strcmp(argv[cmd_idx], "cd") == 0)   {
						if (cmd_idx + 1 < len_argv) {
							if(chdir(argv[cmd_idx+1]) == -1) {
								ft_putstr("error: cd: cannot change directory to ", STDERR_FILENO);
								ft_putstr_endl(argv[cmd_idx+1], STDERR_FILENO);
							}
						} else 
							ft_putstr_endl("error: cd: bad arguments", STDERR_FILENO);
						if (close(tmpfd) == -1)
								fatal_error();
						exit(EXIT_SUCCESS);
				}
				else
						ft_execve(argv+cmd_idx, tmpfd, envp);
		}
		int wstatus;
		if (waitpid(-1, &wstatus, 0) == -1)
				fatal_error();
}

int main(int argc, char* argv[], char *const envp[]) {
		if (argc < 2)
				return 0;	

		int idx_last_cmd = 1;
		int tmpfd = dup(STDIN_FILENO);
		if (tmpfd == -1)
				fatal_error();
		for (int i = 1; i < argc; i++) {
				if (argv[i][0] == ';') {
						if (i == idx_last_cmd) 
								idx_last_cmd++;
						else {
								argv[i] = NULL;
								exec_pipe(argv+idx_last_cmd, i-idx_last_cmd, tmpfd, envp);
								idx_last_cmd = i+1;
						}
				}
		}

		if (idx_last_cmd < argc)  
				exec_pipe(argv+idx_last_cmd, argc-idx_last_cmd, tmpfd, envp);
		close(tmpfd);
		return 0;
}

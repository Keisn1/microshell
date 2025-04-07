test:
	cc -g -Wall -Werror -Wextra -fsanitize=address microshell.c utils.c -o microshell
	bash test.sh

test-valgrind:
	cc -Wall -Werror -Wextra microshell.c utils.c -o microshell
	bash test_with_valgrind.sh

fclean:
	rm microshell

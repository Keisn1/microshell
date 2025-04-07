#!/bin/bash

test() {
	local got="$1"
	local want="$2"
	if [[ "$got" != "$want" ]]; then
		echo "Output don't match!!!"
        echo "got (${#got} chars) = '$got'"
        echo "want (${#want} chars) = '$want'"
	fi
}

got=$(valgrind --track-fds=yes ./microshell "non-executable" 2>&1)
want="error: cannot execute non-executable" 
test "$got" "$want"

got=$(valgrind --track-fds=yes ./microshell /usr/bin/echo Hello)
want="Hello" 
test "$got" "$want"

got=$(valgrind --track-fds=yes ./microshell non-executable ";" /usr/bin/echo "Hello" 2>&1)
want='error: cannot execute non-executable
Hello'
test "$got" "$want"

got=$(valgrind --track-fds=yes ./microshell non-executable ";" /usr/bin/echo "Hello" 2>&1)
want='error: cannot execute non-executable
Hello'
test "$got" "$want"

got=$(valgrind --track-fds=yes ./microshell /usr/bin/echo microshell ";" /bin/echo i love my microshell 2>&1)
want='microshell
i love my microshell'
test "$got" "$want"

got=$(valgrind --track-fds=yes ./microshell /usr/bin/echo first_pipe "|" /usr/bin/cat 2>&1)
want='first_pipe'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell /usr/bin/echo first_pipe "|" /usr/bin/cat "|" /usr/bin/cat 2>&1)
want='first_pipe'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell cd 2>&1)
want='error: cd: bad arguments'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell /usr/bin/echo hello ";" cd 2>&1)
want='hello
error: cd: bad arguments'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell cd asdf 2>&1)
want='error: cd: cannot change directory to asdf'
test "$got" "$want"
got=$(./microshell cd 2>&1)
want='error: cd: bad arguments'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell /usr/bin/echo hello ";" cd 2>&1)
want='hello
error: cd: bad arguments'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell cd asdf 2>&1)
want='error: cd: cannot change directory to asdf'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell cd 2>&1)
want='error: cd: bad arguments'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell /usr/bin/echo hello ";" cd 2>&1)
want='hello
error: cd: bad arguments'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell cd asdf 2>&1)
want='error: cd: cannot change directory to asdf'
test "$got" "$want"

got=$(valgrind --leak-check=full --track-fds=yes ./microshell ";" ";" 2>&1)
want=''
test "$got" "$want"

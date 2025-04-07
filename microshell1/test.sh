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

got="$(./microshell "non-executable" 2>&1)"
want="error: cannot execute non-executable" 
test "$got" "$want"

got="$(./microshell "other non-executable" 2>&1)"
want="error: cannot execute non-executable" 
test "$got" "$want"


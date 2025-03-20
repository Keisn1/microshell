#!/bin/bash

got=$(./microshell "non-executable" 2>&1 )
want="error: cannot execute non-executable"

if [[ "$got" == "$want" ]]; then
	    echo "Output matches expected output."
else
	    echo "Output don't match!!!"
		echo "got = " $got
		echo "want = " $want
fi	

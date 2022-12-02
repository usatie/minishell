#!/bin/bash

assert() {
	echo -n "$1:"
	echo "$1" | ./minishell >out 2>/dev/null
	actual=$?
	echo "$1" | bash >cmp 2>/dev/null
	expected=$?
	diff out cmp && echo -n "diff OK" || terminate=1
	if [ "$actual" = "$expected" ]; then
		echo ", status OK"
	else
		echo ", status NG"
		terminate=1
	fi

	if [ "$terminate" = "1" ]; then
		exit
	fi
}

assert ""
assert "exit"
assert "pwd"
assert "ls | grep .c"
assert "invalid command"

echo "OK :D"

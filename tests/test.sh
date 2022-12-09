#!/bin/bash

cleanup() {
	rm -f cmp out
	rm -f "$1".cmp "$1".out
}

assert() {
	printf "%-30s:" "[$1]"

	echo -e "$1" | ./minishell >out 2>/dev/null
	actual=$?
	if [ $# -eq 2 ]; then
		mv "$2" "$2".out
	fi

	echo -e "$1" | bash >cmp 2>/dev/null
	expected=$?
	if [ $# -eq 2 ]; then
		mv "$2" "$2".cmp
	fi

	diff out cmp && echo -n "diff OK" || terminate=1
	if [ "$terminate" = "1" ]; then
		echo "diff NG"
		cleanup $2
		exit
	fi

	if [ "$actual" = "$expected" ]; then
		echo -n ", status OK"
	else
		echo ", status NG. Expected $expected, actual is $actual"
		terminate=1
		cleanup $2
		exit
	fi

	if [ $# -eq 2 ]; then
		diff "$2".out "$2".cmp && echo ", diff $2 OK" || terminate=1
		if [ "$terminate" = "1" ]; then
			echo ", diff $2 NG"
			cleanup $2
			exit
		fi
	else
		echo
	fi

	cleanup $2
}

assert ""
assert "exit"
assert "pwd"
assert "invalid command"
assert 'exit\npwd'
assert 'cat Makefile'
assert 'cat -e Makefile'
assert 'grep mini Makefile'
assert '/bin/cat Makefile'
assert './tests/hello.sh'
assert "echo 'hello'"
assert 'echo "hello"'
assert "echo '\"hello\"'"
assert "echo \"'hello'\""
assert "     pwd   "
assert "echo hello'world'\"42\""
assert 'ec"ho" he"ll"o'
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello 1>hello.txt' 'hello.txt'
assert 'invalid 2>hello.txt' 'hello.txt'
# assert "ls -l"  # This test fails because out and cmp affects the output of `ls`

echo "OK :D"

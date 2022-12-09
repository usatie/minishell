#!/bin/bash

cleanup() {
	rm -f cmp out
	rm -f "$1".cmp "$1".out
}

assert_output() {
	printf "%-30s:" "[$1]"

	echo -e "$1" | ./minishell >out 2>/dev/null
	actual=$?
	mv "$2" "$2".out

	echo -e "$1" | bash >cmp 2>/dev/null
	expected=$?
	mv "$2" "$2".cmp

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

	diff "$2".out "$2".cmp && echo ", diff $2 OK" || terminate=1
	if [ "$terminate" = "1" ]; then
		echo ", diff $2 NG"
		cleanup $2
		exit
	fi

	cleanup $2
}

assert() {
	printf "%-30s:" "[$1]"
	echo -e "$1" | ./minishell >out 2>/dev/null
	actual=$?
	echo -e "$1" | bash >cmp 2>/dev/null
	expected=$?
	diff out cmp && echo -n "diff OK" || terminate=1
	if [ "$terminate" = "1" ]; then
		echo "diff NG"
		cleanup
		exit
	fi

	if [ "$actual" = "$expected" ]; then
		echo ", status OK"
	else
		echo ", status NG. Expected $expected, actual is $actual"
		terminate=1
		cleanup
		exit
	fi

	cleanup
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
assert_output 'echo hello >hello.txt' 'hello.txt'
assert_output 'echo hello 1>hello.txt' 'hello.txt'
assert_output 'invalid 2>hello.txt' 'hello.txt'
# assert "ls -l"  # This test fails because out and cmp affects the output of `ls`

echo "OK :D"

#!/bin/bash

cleanup() {
	rm -f cmp out
	exit
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
	fi

	if [ "$actual" = "$expected" ]; then
		echo ", status OK"
	else
		echo ", status NG. Expected $expected, actual is $actual"
		terminate=1
	fi

	if [ "$terminate" = "1" ]; then
		cleanup
	fi
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
# assert "ls -l"  # This test fails because out and cmp affects the output of `ls`

echo "OK :D"
cleanup

#!/bin/bash

cleanup() {
	rm -f cmp out
	rm -f "$1".cmp "$1".out
}

assert() {
	printf "%-50s:" "[$1]"

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
# assert 'invalid 2>hello.txt' 'hello.txt'
assert 'cat Makefile | grep minishell'
assert 'cat Makefile | grep c | sort -r'
assert 'cat Makefile | grep c | sort -r > sort.txt' 'sort.txt'
assert 'cat Makefile | grep l > grep.txt | sort -r' 'grep.txt'
assert 'echo 111111111111111111111111111111'
assert 'echo $USER'
assert 'echo hello$USER'
assert 'echo hello "Mr. "$USER'

# Variable in quotes
assert 'echo "$USER"'
assert 'echo "Variable with text $USER"'
assert 'echo "Variable $USER between text"'
assert 'echo "Multiple $USER variables $SHELL"'
assert 'echo "Variables non-space $USER.$SHELL+$HOME"'
assert 'echo "Undefined variable $undefined_variable"'
assert 'echo "These are not variable : $. $+ "'
assert 'echo "These are variable     : $_foo $foo"'

# Special Parameter
assert 'echo $?'
assert 'echo "$?"'

# Word splitting
# export foo="a     b"
# assert 'echo "$foo"'
# assert 'echo $foo'

# assert "ls -l"  # This test fails because out and cmp affects the output of `ls`

# Builtin
assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd' # bash doesn't follow symlink? or cd/pwd implementation is strange?
# assert 'env' # output doesn't match bash's
assert 'env | grep "USER"'
assert 'export foo=bar\nenv | grep "foo=bar"'
assert 'export foo=bar\nunset foo\necho $foo'
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'
assert 'exit 42'
assert '>>>\nexit'

echo "OK :D"

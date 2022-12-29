#!/bin/bash

cleanup() {
	rm -f cmp out
	rm -f "$1".cmp "$1".out
	rm -f test_*.txt
	rm -f test_sigint
}


test_sigint() {
	printf "%-80s:" "[test_sigint] Please press Ctrl-C 2 times"

	echo "int main() { while (1) ; }" | gcc -xc -o test_sigint -
	echo "./test_sigint" | ./minishell 2>&- || actual=$?
	echo "./test_sigint" | bash 2>&- || expected=$?
	if [ "$actual" = "$expected" ]; then
		echo "status OK"
	else
		echo "status NG. Expected $expected, actual is $actual"
	fi
	cleanup
}

assert_syntax_error() {
	printf "%-80s:" "[$1]"
	echo -e "$1" | ./minishell >out 2>/dev/null
	touch cmp
	actual=$?
	expected=258
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
		cleanup $2
		exit
	fi
	cleanup
}

assert() {
	printf "%-80s:" "[$1]"

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
assert 'echo 1.txt'
assert '\n\n\n'
assert 'invalid command\n\n\n'
assert '>tmp.txt' 'tmp.txt'
assert '>>tmp.txt' 'tmp.txt'
assert '<tmp.txt'
assert '<<EOF'
assert 'echo hello >tmp \n >tmp' 'tmp'
assert 'echo hello >tmp \n >>tmp' 'tmp'
assert 'echo hello >tmp \n <tmp' 'tmp'

# Redirection
## Redirect Output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello 1>hello.txt' 'hello.txt'
# assert 'invalid 2>hello.txt' 'hello.txt'
assert 'echo 1>test_one.txt 2>test_two.txt 3>test_three.txt'
assert 'echo 1>test_one.txt 2>test_two.txt 3>test_three.txt\npwd'
assert 'echo hello >>hello.txt >>hello.txt' 'hello.txt'
assert 'echo hello >hello.txt \n echo world >>hello.txt \n echo hello >hello.txt' 'hello.txt'

## Redirect Input
echo hello > test_hello.txt
assert 'cat <test_hello.txt'
# echo 0 >test_zero.txt && echo 1 >test_one.txt && echo 2 >test_two.txt && echo 3 >test_three.txt
# assert 'cat 0<test_zero.txt 1<test_one.txt 2<test_two.txt 3<test_three.txt'
# echo 0 >test_zero.txt && echo 1 >test_one.txt && echo 2 >test_two.txt && echo 3 >test_three.txt
# assert 'echo 1<test_one.txt 2<test_two.txt 3<test_three.txt'

## Heredoc
assert 'cat <<EOF          \nhello\nworld\nEOF'
assert 'cat <<EOF <<EOF2   \nhello\nEOF\nworld\nEOF2'
assert 'cat <<EOF | cat <<EOF2 | cat <<EOF3\nhello\nEOF\nworld\nEOF242Tokyo\nEOF3'
assert 'cat <<EOF          \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<E"O"F        \nhello\nworld\nEOF'
export EOF="eof"
assert 'cat <<$EOF         \neof\n$EOF\nEOF'
assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'
unset EOF
export E="e"
export O="o"
export F="f"
assert 'cat <<$E"of"       \n$E"of"\n$Eof\neof'
assert 'cat <<e$O$F       \n$E"of"\n$Eof\ne$O$F\neof'
unset E
unset O
unset F
assert 'cat <<EOF\nHello $USER $FOO $BAR $USER'

# Pipe
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

# Variable
export foo="pwd"
assert '$foo'
export foo="hello.txt"
assert 'echo hello >$foo' 'hello.txt'
unset foo

# Special Parameter
assert 'echo $?'
assert 'echo "$?"'

# Word splitting
# export foo="a     b"
# assert 'echo "$foo"'
# assert 'echo $foo'
# export foo="echo hello           world       42Tokyo"
# assert '$foo'
# unset foo

# assert "ls -l"  # This test fails because out and cmp affects the output of `ls`

# Builtin
## cd/pwd
assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
assert 'cd . \n pwd \n echo $PWD $OLDPWD'
assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp \n cd /etc \n cd - \n cd - \n cd - \n cd - \n'
assert 'cd .. \n cd minishell/ \n unset PWD \n cd src/ \n cd .. \n cd -'

## env
# assert 'env' # output doesn't match bash's
assert 'env | grep "USER"'

## export
assert 'export foo=bar\nenv | grep "foo=bar"'
assert 'export bar \n env | grep bar'
assert 'export foobar \n export | grep foobar'
assert 'export ""'
assert 'export 1'
assert 'export $'
assert 'export ?'
assert 'export ='
assert 'export =='

## unset
assert 'export foo=bar \n unset foo \n echo $foo'
assert 'export foo=bar \n unset foo \n export | grep foo'
assert 'export foo     \n unset foo \n export | grep foo'

## echo
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'

## exit
assert 'exit 42'
assert '>>>\nexit'
assert 'exit hello'
assert 'exit 1 2 3'
assert 'exit 123abc'
assert 'exit 9999999999999999999999'

# Edge case
## search_path
### executable in current directory
cat >hello.sh <<EOF
#!/bin/bash
echo hello
EOF
assert 'hello.sh'
assert './hello.sh'
chmod +x hello.sh
assert 'hello.sh'
assert './hello.sh'
mv hello.sh ls
assert 'export PATH=.:/bin \n ls src'
assert 'export PATH=/bin:. \n ls src'
rm -f ls
### same name in two directories
mkdir -p /tmp/a /tmp/b
echo -e '#!/bin/bash'"\necho hello a" >/tmp/a/hello.sh
echo -e '#!/bin/bash'"\necho hello b" >/tmp/b/hello.sh
assert 'export PATH=/tmp/a:/tmp/b \n hello.sh'
assert 'export PATH=/tmp/b:/tmp/a \n hello.sh'
chmod +x /tmp/a/hello.sh
assert 'export PATH=/tmp/a:/tmp/b \n hello.sh'
assert 'export PATH=/tmp/b:/tmp/a \n hello.sh'
chmod -x /tmp/a/hello.sh
chmod +x /tmp/b/hello.sh
assert 'export PATH=/tmp/a:/tmp/b \n hello.sh'
assert 'export PATH=/tmp/b:/tmp/a \n hello.sh'
rm -rf /tmp/a /tmp/b

assert '""'
assert '..'
# assert '.' # . is a builtin command in bash
assert './'
assert '/'
assert '/etc'
assert '/etc/'
assert '////'
# assert '.' # Bash's `.` is a builtin command
assert 'echo hello>test_1.txt>test_2.txt>test_3.txt' 'test_3.txt'
assert 'ls|grep mini|sort -r|wc>test.txt' 'test.txt'

# syntax error
# assert_syntax_error 'echo ||'
assert 'echo |'
assert 'echo | |'
assert '| | |'

# signal
test_sigint

echo "OK :D"

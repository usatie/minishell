#!/bin/bash
assert() {
    printf "%-50s:" "$1"

    echo -e "$1" | bash

    echo -e -n "$1" | bash >out 2>/dev/null
    expected=$?

#    printf "" "$out"

    printf "%-50s:" ""
    printf "exit_status=%-3s" "$expected"

    if [ $# -eq 2 ]; then
        mv "$2" "$2".out
        printf "out_file=%-10s\n" "$2"
        rm -f *.out
    fi
    rm -f out

    printf "\n\n"
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

echo "OK :D"

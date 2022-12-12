#!/bin/bash -e 

assert() {
    echo -n "$1:"
    echo "$1" | ./minishell > out
    echo "$1" | bash > cmp
    diff out cmp
    echo "OK"
}

assert "exit"
assert "pwd"
assert "ls | grep .c"

echo "OK :D"

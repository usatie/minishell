#!/bin/bash

echo "exit" | ./minishell > out
echo "exit" | bash > cmp
diff out cmp

echo "OK :D"

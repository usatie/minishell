NAME	= minishell
CFLAGS	= -Wall -Werror -Wextra

$(NAME): minishell.c
	gcc minishell.c -o $(NAME) -lreadline $(CFLAGS)

test: $(NAME)
	./tests/test.sh

.PHONY: test

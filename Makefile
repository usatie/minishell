NAME	= minishell
CFLAGS	= -Wall -Werror -Wextra

$(NAME): minishell.c
	gcc minishell.c -o $(NAME) -lreadline $(CFLAGS)

test: $(NAME)
	bash test.sh

.PHONY: test
NAME	= minishell
CFLAGS	= -Wall -Werror -Wextra
SRCS    = src/minishell.c
OBJS    = $(SRCS:%.c=%.o)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME) -lreadline $(CFLAGS)

test: $(NAME)
	./tests/test.sh

.PHONY: test

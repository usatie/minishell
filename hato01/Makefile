NAME	 = minishell
CC       = cc
CFLAGS	 = -Wall -Werror -Wextra
INCLUDES = -I include

LIBFTDIR = libft
LIBFT    = libft/libft.a

LIBS     = -lreadline -lft -L libft
SRCS     = src/minishell.c
OBJDIR   = obj
OBJS     = $(SRCS:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o: src/%.c
	mkdir -p $(OBJDIR)
	$(CC) $^ -o $@ -c $(CFLAGS) $(INCLUDES)

$(LIBFT):
	make -C $(LIBFTDIR)

test: $(NAME)
	./tests/test.sh

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: test all clean fclean re

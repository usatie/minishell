NAME	  = minishell
CC        = cc
CFLAGS	  = -Wall -Werror -Wextra # compiler flags
INCLUDES  = -I include
LIBS      = -lreadline            # linker flags
SRCS      = src/minishell.c
OBJDIR    = obj
OBJS      = $(SRCS:src/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o: src/%.c
	mkdir -p $(OBJDIR)
	$(CC) $^ -o $@ -c $(CFLAGS) $(INCLUDES)

test: $(NAME)
	./tests/test.sh

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: test all clean fclean re

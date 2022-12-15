NAME	  = minishell
CC        = cc
CFLAGS	  = -Wall -Werror -Wextra # compiler flags
INCLUDES  = -I include
LIBFTDIR  = libft
LIBFT     = libft/libft.a
LIBS      = -lreadline -lft -L libft          # linker flags
SRCS      = src/minishell.c\
            src/tokenize.c\
            src/parse.c\
            src/error.c\
			src/gen_pipeline.c\
			src/fork_exec.c\
			src/expand.c\
			src/builtin.c\
			src/node.c\
			src/str.c\
			src/token.c
OBJDIR    = obj
OBJS      = $(SRCS:src/%.c=$(OBJDIR)/%.o)
DEPS      = $(SRCS:src/%.c=$(OBJDIR)/%.d)
.PHONY: $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -MMD -MP -c $< -o $@ $(CFLAGS) $(INCLUDES)

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
-include $(DEPS)

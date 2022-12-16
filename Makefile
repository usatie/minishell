NAME	  = minishell
CC        = cc
CFLAGS	  = -Wall -Werror -Wextra # compiler flags
RLDIR     = $(shell brew --prefix readline)
INCLUDES  = -I include -I $(RLDIR)/include
LIBFTDIR  = libft
LIBFT     = libft/libft.a
LIBS      = -lreadline -L$(RLDIR)/lib -lft -L libft          # linker flags
SRCS      = src/minishell.c\
            src/tokenize.c\
            src/parse.c\
            src/error.c\
			src/gen_pipeline.c\
			src/fork_exec.c\
			src/expand.c\
			src/node.c\
			src/str.c\
			src/token.c\
			src/ft_syscall.c\
			src/builtin/builtin.c\
			src/builtin/ft_echo.c\
			src/builtin/ft_cd.c\
			src/builtin/ft_pwd.c\
			src/builtin/ft_export.c\
			src/builtin/ft_unset.c\
			src/builtin/ft_env.c\
			src/builtin/ft_exit.c\
			src/signal.c\
			src/termios.c\
			src/readline.c\

OBJDIR    = obj
OBJS      = $(SRCS:src/%.c=$(OBJDIR)/%.o)
DEPS      = $(SRCS:src/%.c=$(OBJDIR)/%.d)
.PHONY: $(DEPS)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(@D)
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

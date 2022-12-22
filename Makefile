NAME	  = minishell
CC        = cc
CFLAGS	  = -Wall -Werror -Wextra # compiler flags
RLDIR     = $(shell brew --prefix readline)
INCLUDES  = -I include -I $(RLDIR)/include
LIBFTDIR  = libft
LIBFT     = libft/libft.a
LIBS      = -lreadline -L$(RLDIR)/lib -lft -L libft          # linker flags
SRCS      = src/minishell.c\
            src/error.c\
			src/ft_syscall.c\
			src/ft_string.c\
			src/destructor.c\
			src/setup/signal.c\
			src/setup/readline.c\
            src/tokenize/tokenize.c\
			src/tokenize/token.c\
			src/tokenize/str.c\
			src/tokenize/str_tokenize.c\
            src/parse/parse.c\
			src/parse/node.c\
			src/pipeline/pipeline.c\
			src/gen/gen.c\
			src/expand/expand.c\
			src/expand/expand_line.c\
			src/redirect/heredoc.c\
			src/redirect/redirect.c\
			src/exec/exec.c\
			src/exec/fork_exec.c\
			src/exec/builtin/builtin.c\
			src/exec/builtin/ft_echo.c\
			src/exec/builtin/ft_cd.c\
			src/exec/builtin/ft_pwd.c\
			src/exec/builtin/ft_export.c\
			src/exec/builtin/ft_unset.c\
			src/exec/builtin/ft_env.c\
			src/exec/builtin/ft_exit.c\

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
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

norm:
	norminette include src libft\
		| grep Error\
		| grep -v 'WRONG_SCOPE_COMMENT'\

.PHONY: test all clean fclean re
-include $(DEPS)

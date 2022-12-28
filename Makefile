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
			src/lib/ft_syscall.c\
			src/lib/ft_putenv.c\
			src/lib/ft_setenv.c\
			src/lib/ft_unsetenv.c\
			src/lib/ft_getenv.c\
			src/lib/ft_string.c\
			src/lib/ft_string2.c\
			src/lib/is_valid_fd.c\
			src/lib/stashfd.c\
			src/lib/filepath.c\
			src/destructor/free_str.c\
			src/destructor/free_tok.c\
			src/destructor/free_node.c\
			src/destructor/free_pipeline.c\
			src/setup/signal.c\
			src/setup/readline.c\
            src/tokenize/tokenize.c\
			src/tokenize/token.c\
			src/tokenize/str.c\
			src/tokenize/str_to_word.c\
			src/tokenize/str_tokenize.c\
            src/tokenize/error.c\
            src/parse/parse.c\
			src/parse/node.c\
			src/parse/util.c\
			src/parse/num.c\
			src/parse/word.c\
			src/parse/simple_command.c\
			src/parse/pipeline.c\
			src/parse/redirection.c\
			src/gen/pipeline.c\
			src/gen/gen.c\
			src/expand/expand.c\
			src/expand/expand_line.c\
			src/redirect/heredoc.c\
			src/redirect/redirect.c\
			src/exec/exec.c\
			src/exec/ft_execvp.c\
			src/exec/pipe.c\
			src/exec/search_path.c\
			src/exec/exec_pipelines.c\
			src/exec/builtin/builtin.c\
			src/exec/builtin/env_name.c\
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
		| grep -v 'WRONG_SCOPE_COMMENT'
	nm -u $(NAME) | grep -v -E "_(readline|rl_clear_history|rl_on_new_line|\
	rl_replace_line|rl_redisplay|add_history|printf|malloc|free|write|\
	access|open|read|close|fork|wait|waitpid|wait3|wait4|signal|\
	sigaction|sigemptyset|sigaddset|kill|exit|getcwd|chdir|stat|lstat|\
	fstat|unlink|execve|dup|dup2|pipe|opendir|readdir|closedir|\
	strerror|perror|isatty|ttyname|ttyslot|ioctl|getenv|tcsetattr|\
	tcgetattr|tgetent|tgetflag|tgetnum|tgetstr|tgoto|tputs)"
.PHONY: test all clean fclean re
-include $(DEPS)

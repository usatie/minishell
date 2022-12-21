/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 15:38:49 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stddef.h>
# include <stdbool.h>

// for printf debug
# include <stdio.h>
# include <string.h>
# include <signal.h>

typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef enum e_token_kind	t_token_kind;
typedef struct s_str		t_str;
typedef enum e_str_kind		t_str_kind;
typedef struct s_node		t_node;
typedef enum e_node_kind	t_node_kind;
typedef struct s_pipeline	t_pipeline;

extern char					**environ;
extern t_env				g_env;

struct s_env {
	int				status;
	t_pipeline		*pipeline;
	sig_atomic_t	sig;
	bool			syntax_error;
	bool			heredoc_interrupted;
};

enum e_token_kind {
	TK_PUNCT, // Punctuator
	TK_STRING, // String (plain text, single quotes, double quotes)
	TK_NUM, // Integer Literal
	TK_EOF, // EOF
};

enum e_str_kind {
	STR_PLAIN, // str
	STR_SINGLE, // 'str'
	STR_DOUBLE, // "str"
	STR_VAR, // $variable
	STR_SPECIAL_PARAM, // $?
};

// echo "hello $USER $USER world" "world!"
// pos: ^
// len: 7
//        pos: ^
//        len: 5
//              pos: ^
//              len: 5
struct s_str {
	t_str_kind	kind;
	char		*pos;
	size_t		len;
	t_str		*next;

	// Only for STR_DOUBLE
	t_str		*parameters;

	// Only for STR_VAR
	char		*value;
	size_t		value_len;
};

struct s_token {
	char			*pos;
	size_t			len;
	t_token_kind	kind;
	t_token			*next;

	// Only for TK_STRING
	t_str			*str;

	// Only for TK_NUM
	long			val;
};

enum e_node_kind {
	ND_WORD,
	ND_NUM,
	ND_REDIR_OUT,
	ND_REDIR_IN,
	ND_REDIR_APPEND,
	ND_REDIR_HEREDOC,
	ND_CMD,
	ND_PIPE,
};

struct s_node {
	t_node_kind	kind;
	t_node		*next;
	t_token		*tok;

	pid_t		pid;
	// ND_PIPE, ND_REDIR_*
	t_node		*lhs;
	t_node		*rhs;

	// Only for ND_CMD
	int			nargs;
	t_node		*args;
	t_node		*redirects;

	// Only for ND_WORD;
	t_str		*str;

	// Only for ND_NUM
	long		val;
};

typedef struct s_redirect		t_redirect;
typedef enum e_redirect_kind	t_redirect_kind;

enum e_redirect_kind {
	RD_OUTPUT,
	RD_INPUT,
	RD_APPEND,
	RD_HEREDOC,
};

struct s_redirect {
	t_redirect_kind	kind;
	int			fd;
	int			tmpfd;
	int			srcfd;
	t_redirect	*next;

	// OUTPUT, INPUT, APPEND
	char		*path;

	// HEREDOC
	char		*delimiter;
	bool		is_delim_quoted;
};

struct s_pipeline {
	pid_t		pid;
	char		**argv;
	int			inpipe[2];
	int			outpipe[2];
	t_redirect	*redirects;
	t_pipeline	*next;
};

// error.c
void	fatal_exit(char *s) __attribute__((noreturn));
void	err_exit(char *s) __attribute__((noreturn));

// tokenizer.c
bool	startswith(const char *p, const char *q);
t_token	*tokenize(char *line);

// expand.c
void	expand(t_node *node);
char	*expand_line(char *line);

// parser.c
t_node	*parse(t_token *tok);

// str.c
t_str	*new_str(char *pos, size_t len, t_str_kind kind);

// token.c
t_token	*new_token(char *pos, size_t len, t_token_kind kind);
bool	startswith(const char *p, const char *q);

// node.c
t_node	*new_node(t_node_kind kind, t_token *tok);
t_node	*new_node_binary(t_node_kind kind, t_node *lhs, t_node *rhs, t_token *tok);
t_node	*new_node_num(long val, t_token *tok);
t_node	*add_node_back(t_node *head, t_node *new_node);
bool	equal(const t_token *tok, const char *op);
bool	at_eof(const t_token *tok);

// quotes.c
char	*convert_to_word(t_str *str);

// pipeline.c
t_pipeline	*new_pipeline(void);
t_pipeline	*connect_pipeline(t_pipeline *lhs, t_pipeline *rhs);

// gen.c
t_pipeline	*gen_pipelines(t_node *node);

// builtin.c
bool	isbuiltin(char *command);
int		exec_builtin(t_pipeline *pipeline);

// builtin/ft_*.c
int	ft_echo(char *argv[]);
int	ft_cd(char **argv);
int	ft_pwd(char *argv[]);
int	ft_export(char **argv);
int	ft_unset(char *argv[]);
int	ft_env(char **argv);
int	ft_exit(char **argv);

// fork_exec.c
int		forkexec_pipeline(t_pipeline *head);

// ft_syscall.c
int		ft_open(char *path, int oflag, mode_t mode);
void	ft_close(int fd);
pid_t	ft_fork(void);
void	ft_dup2(int oldfd, int newfd);
int		stashfd(int fd);
bool	is_valid_fd(int fd);

// ft_string.c
bool	is_blank(char c);
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
bool	is_metachr(char c);
bool	is_control_operator(const char *s);
bool	is_variable(const char *s);
bool	is_specialchr(char c);
bool	is_special_param(const char *s);
bool	is_unquoted(const char *s);
bool	is_number(const char *s);

// termios.c
void	setup_term(void);

// signal.c
void	setup_signal(void);

// readline.c
void	setup_rl(void);

// redirect.c
t_redirect	*new_redirect(t_redirect_kind kind, char *path, int fd);
t_redirect	*add_redir_back(t_redirect *head, t_redirect *new_redir);
void		redirect(t_redirect *redir);
void		restore_redirect(t_redirect *redir);
void		open_srcfd(t_redirect *redir);
void		close_srcfd(t_redirect *redir);

// heredoc.c
int	read_heredoc(const char *delimiter, bool is_delim_quoted);

#endif

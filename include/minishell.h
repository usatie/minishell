/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/16 16:41:05 by susami           ###   ########.fr       */
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
	int			status;
	t_pipeline	*pipeline;
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
	ND_CMD,
	ND_PIPE,
};

struct s_node {
	t_node_kind	kind;
	t_node		*next;
	t_token		*tok;

	pid_t		pid;
	// ND_PIPE, ND_REDIRECT_*
	t_node		*lhs;
	t_node		*rhs;

	// Only for ND_CMD
	int			nargs;
	t_node		*args;
	t_node		*redir_out;

	// Only for ND_WORD;
	t_str		*str;

	// Only for ND_NUM
	long		val;
};

struct s_pipeline {
	pid_t		pid;
	char		**argv;
	int			inpipe[2];
	int			outpipe[2];
	char		*out_path;
	int			out_fd;
	int			out_dupfd;
	t_pipeline	*next;
};

// error.c
void	fatal_exit(char *s) __attribute__((noreturn));
void	err_exit(char *s) __attribute__((noreturn));

// tokenizer.c
bool	startswith(const char *p, const char *q);
t_token	*tokenize(char *line);

// expansion.c
void	expand_parameter(t_token *tok);

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
bool	equal(t_token *tok, char *op);
bool	at_eof(t_token *tok);

// quotes.c
char	*convert_to_word(t_str *str);

// gen_command.c
t_pipeline	*gen_pipeline(t_node *node);

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
int		ft_open(char *path);
void	ft_close(int fd);
pid_t	ft_fork(void);
int		ft_dup(int oldfd);
void	ft_dup2(int oldfd, int newfd);

// termios.c
void	setup_term(void);

// signal.c
void	setup_signal(void);

// readline.c
void	setup_rl(void);

#endif

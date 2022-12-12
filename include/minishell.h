/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/13 06:59:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_token		t_token;
typedef enum e_token_kind	t_token_kind;

enum e_token_kind {
	TK_PUNCT, // Punctuator
	TK_STRING, // String (plain text, single quotes, double quotes)
	TK_NUM, // Integer Literal
	TK_EOF, // EOF
};

typedef struct s_str		t_str;
typedef enum e_str_kind		t_str_kind;

enum e_str_kind {
	STR_PLAIN, // str
	STR_SINGLE, // 'str'
	STR_DOUBLE, // "str"
	STR_VAR, // $variable
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
	t_str		*variables;

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

typedef struct s_node		t_node;
typedef enum e_node_kind	t_node_kind;
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

typedef struct s_pipeline	t_pipeline;
struct s_pipeline {
	pid_t		pid;
	char		**argv;
	int			inpipe[2];
	int			outpipe[2];
	char		*out_path;
	int			out_fd;
	t_pipeline	*next;
};

// error.c
void	fatal_exit(char *s) __attribute__((noreturn));
void	err_exit(char *s) __attribute__((noreturn));

// tokenizer.c
t_token	*tokenize(char *line);

// expansion.c
void	expand_parameter(t_token *tok);

// parser.c
t_node	*parse(char *line);

// quotes.c
char	*convert_to_word(t_str *str);

// gen_command.c
t_pipeline	*gen_pipeline(t_node *node);

// fork_exec.c
void	ft_close(int fd);
pid_t	ft_fork(void);
void	ft_dup2(int oldfd, int newfd);
void	forkexec(t_pipeline *command);

// main.c
char	*find_path(char *cmd);
#endif

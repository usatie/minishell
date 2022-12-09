/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 18:20:07 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
};

struct s_str {
	t_str_kind	kind;
	char		*pos;
	size_t		len;
	t_str		*next;
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
	ND_REDIRECT_OUTPUT,
	ND_CMD,
};

struct s_node {
	t_node_kind	kind;
	t_node		*next;
	t_token		*tok;

	// Only for ND_CMD
	t_node		*elements;

	// Only for ND_WORD and ND_REDIRECT_*;
	t_str		*str;

	// Only for ND_REDIRECT_*
	int			fd;
};

typedef struct s_command	t_command;
struct s_command {
	char	*path;
	char	*argv[100];
	char	*out_path;
	int		out_fd;
};

// error.c
void	fatal_exit(char *s) __attribute__((noreturn));
void	err_exit(char *s) __attribute__((noreturn));

// tokenizer.c
t_token	*tokenize(char *line);

// parser.c
t_node	*parse(t_token *tok);

// quotes.c
char	*convert_to_word(t_str *str);
#endif

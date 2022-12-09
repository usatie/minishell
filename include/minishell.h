/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/09 08:49:14 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

enum e_token_type {
	TK_PUNCT, // Punctuator
	TK_STRING, // String (plain text, single quotes, double quotes)
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
	t_token_type	type;
	t_token			*next;

	// Only for TK_STRING
	t_str			*str;
};

typedef struct s_command	t_command;
struct s_command {
	char	*path;
	char	**argv;
};


// tokenizer.c
t_token	*tokenize(char *line);

// parser.c
t_command	*parse(t_token *tok);

// quotes.c
char	*convert_to_word(t_str *str);
#endif

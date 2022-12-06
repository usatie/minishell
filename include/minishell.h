/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/06 16:36:26 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

enum e_token_type {
	TK_IDENT, // Identifier
	TK_PUNCT, // Punctuator
	TK_SINGLE_QUOTES, // Single quoted string
	TK_DOUBLE_QUOTES, // Double quoted string
	TK_SPACE, // Space
	TK_EOF, // EOF
};

struct s_token {
	char			*pos;
	char			*content; // Only for quoted string
	size_t			len;
	t_token_type	type;
	t_token			*next;
};

typedef struct s_node	t_node;
struct s_node {
	char	*cmd;
	char	*path;
	char	**argv;
};


// tokenizer.c
t_token	*tokenize(char *line);

// parser.c
t_node	*parse(t_token *tok);
#endif

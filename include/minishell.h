/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:06:35 by susami            #+#    #+#             */
/*   Updated: 2022/12/06 14:26:16 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token		t_token;
typedef enum e_token_type	t_token_type;

enum e_token_type {
	TK_IDENT, // Identifier
	TK_PUNCT, // Punctuator
	TK_SINGLE_QUOTES, // Single quoted string
	TK_DOUBLE_QUOTES, // Double quoted string
};

struct s_token {
	char			*pos;
	char			*content; // Only for quoted string
	size_t			len;
	t_token_type	type;
	t_token			*next;
};

// tokenizer.c
t_token	*tokenize(char *line);
#endif

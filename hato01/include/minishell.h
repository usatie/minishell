/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:11:58 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/23 06:59:28 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "../libft/libft.h"

#define PROMPT "minishell > "

typedef struct s_token			t_token;
typedef enum e_token_type		t_token_type;

enum e_token_type {
	TK_IDENT, // Identifier
	TK_PUNCT, // Punctuator
};

struct s_token {
	char			*pos;
	size_t			len;
	t_token_type	type;
	t_token			*next;
};

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:25:51 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 14:52:46 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static bool		consume_blank(char **rest, char *line);
static t_token	*string(char **rest, char *line);
static t_token	*number(char **rest, char *line);

// "cat -e Makefile"
//  ^   ^  ^

// 'echo "hello"'
//  ^    ^ 
t_token	*tokenize(char *line)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		// Multi character punctuator
		else if (startswith(line, "<<") || startswith(line, ">>"))
		{
			cur->next = new_token(line, 2, TK_PUNCT);
			line += 2;
		}
		// Single character punctuator
		else if (ft_strchr("|<>", *line) != NULL)
			cur->next = new_token(line++, 1, TK_PUNCT);
		else if (is_number(line))
			cur->next = number(&line, line);
		else
			cur->next = string(&line, line);
		cur = cur->next;
	}
	cur->next = new_token(line, 0, TK_EOF);
	return (head.next);
}

static bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	return (false);
}

static t_token	*number(char **rest, char *line)
{
	t_token	*tok;

	tok = new_token(line, 0, TK_NUM);
	tok->val = ft_strtol(line, &line, 10);
	tok->len = line - tok->pos;
	tok->str = new_str(STR_PLAIN, tok->pos, tok->len, NULL);
	*rest = line;
	return (tok);
}

static t_token	*string(char **rest, char *line)
{
	t_token	*tok;
	t_str	head;
	t_str	*cur;

	tok = new_token(line, 0, TK_STRING);
	cur = &head;
	while (*line && !is_metachr(*line))
	{
		if (*line == '\'')
			cur->next = single_quotes(&line, line);
		else if (*line == '"')
			cur->next = double_quotes(&line, line);
		else if (is_special_param(line))
			cur->next = special_parameter(&line, line);
		else if (is_variable(line))
			cur->next = variable(&line, line);
		else
			cur->next = plain_text(&line, line);
		cur = cur->next;
		tok->len += cur->len;
	}
	tok->str = head.next;
	*rest = line;
	return (tok);
}

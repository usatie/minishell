/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:34:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 11:36:00 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// echo $USER 
//      ^    ^
// (t_token *) or (t_str *)
//
// echo "hello"$USER"world"
// echo $foo"hello"
// echo "a" "b" "chello"
//
t_str	*variable(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	if (*line != '$')
		fatal_exit("Expected $\n");
	line++;
	if (!is_alpha_under(*line))
		fatal_exit("Expected alphabetic character or underscore.");
	line++;
	while (is_alpha_num_under(*line))
		line++;
	str = new_str(start, line - start, STR_VAR);
	*rest = line;
	return (str);
}

t_str	*special_parameter(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	if (*line != '$')
		fatal_exit("Expected $\n");
	line++;
	if (!is_specialchr(*line))
		fatal_exit("Expected special character.");
	line++;
	str = new_str(start, line - start, STR_SPECIAL_PARAM);
	*rest = line;
	return (str);
}

// Read until next single quote
t_str	*single_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	line++; // skip the opening quote
	while (*line && *line != '\'')
		line++;
	if (*line != '\'')
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	line++;
	str = new_str(start, line - start, STR_SINGLE);
	*rest = line;
	return (str);
}

// Read until next double quote
// $parameter may be contained
t_str	*double_quotes(char **rest, char *line)
{
	t_str	*str;
	char	*start;
	t_str	paramhead;
	t_str	*param;

	paramhead.next = NULL;
	param = &paramhead;
	start = line;
	line++; // skip the opening quote
	while (*line && *line != '"')
	{
		if (is_variable(line))
		{
			param->next = variable(&line, line);
			param = param->next;
		}
		else if (is_special_param(line))
		{
			param->next = special_parameter(&line, line);
			param = param->next;
		}
		else
			line++;
	}
	if (*line != '"')
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	line++;
	str = new_str(start, line - start, STR_DOUBLE);
	str->parameters = paramhead.next;
	*rest = line;
	return (str);
}

// Read until next punctuator or space
t_str	*plain_text(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	while (*line != '\0' && is_unquoted(line))
		line++;
	if (line - start > 0)
	{
		str = new_str(start, line - start, STR_PLAIN);
		*rest = line;
		return (str);
	}
	fatal_exit("Unexpected character\n");
}

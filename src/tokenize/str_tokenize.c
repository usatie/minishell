/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tokenize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:34:21 by susami            #+#    #+#             */
/*   Updated: 2022/12/29 23:05:23 by susami           ###   ########.fr       */
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
	line += 2; // '$' + '[a-zA-z_]' 
	while (is_alpha_num_under(*line))
		line++;
	str = new_str(STR_VAR, start, line - start, NULL);
	*rest = line;
	return (str);
}

t_str	*special_parameter(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	line += 2; // '$' + '?'
	str = new_str(STR_SPECIAL_PARAM, start, 2, NULL);
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
	if (*line == '\'')
		line++;
	else
		tokenize_error("Unclosed single quote", &line, line);
	str = new_str(STR_SINGLE, start, line - start, NULL);
	*rest = line;
	return (str);
}

// Read until next double quote
// $parameter may be contained
t_str	*double_quotes(char **rest, char *line)
{
	char	*start;
	t_str	*params;

	params = NULL;
	start = line;
	line++; // skip the opening quote
	while (*line && *line != '"')
	{
		if (is_variable(line))
			params = add_str_back(params, variable(&line, line));
		else if (is_special_param(line))
			params = add_str_back(params, special_parameter(&line, line));
		else
			line++;
	}
	if (*line == '"')
		line++;
	else
		tokenize_error("Unclosed double quote", &line, line);
	*rest = line;
	return (new_str(STR_DOUBLE, start, line - start, params));
}

// Read until next quotes/parameters/metacharacter
t_str	*plain_text(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	while (*line != '\0' && is_plain_text(line))
		line++;
	str = new_str(STR_PLAIN, start, line - start, NULL);
	*rest = line;
	return (str);
}

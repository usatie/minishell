/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:38:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 15:20:41 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
`man bash`

DEFINITIONS
	The following definitions are used throughout the rest of this document.
	blank	A space or tab.
	word	A sequence of characters considered as a single unit by the shell.
			Also known as a token.
	name	A word consisting only of alphanumeric characters and underscores,
			and beginning with an alphabetic character or an underscore.  Also 
			referred to as an identifier.
	metacharacter
			A character that, when unquoted, separates words.  One of the
			following:
			|  & ; ( ) < > space tab
	control operator
			A token that performs a control function. It is one of the
			following symbols:
			|| & && ; ;; ( ) | <newline>

PARAMETERS
	A parameter is an entity that stores values.  It can be a name, a number,
	or one of the special characters listed below under Special Parameters.
	A variable is a parameter denoted by a name.  A variable has a value and
	zero or more attributes.  Attributes are assigned using the declare builtin
	command (see declare below in SHELL BUILTIN COMMANDS).

	variable
			A parameter denoted by a name.
*/
bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

// | & ; ( ) < > space tab
// & ; ( ) is not supported
bool	is_metachr(char c)
{
	return (ft_strchr("|<>", c) || is_blank(c));
}

// || & && ; ;; ( ) | <newline>
// || & && ; ;; ( ) is not supported
bool	is_control_operator(const char *s)
{
	return (startswith(s, "&&")
		|| startswith(s, "|")
		|| startswith(s, "\n"));
}

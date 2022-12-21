/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:38:04 by susami            #+#    #+#             */
/*   Updated: 2022/12/21 21:25:34 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
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
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_metachr(char c)
{
	//return (strchr("&;()<>", c) || is_blank(c));
	return (strchr("<>", c) || is_blank(c));
}

bool	is_control_operator(const char *s)
{
	return (startswith(s, "&&")
		|| startswith(s, "|")
		|| startswith(s, "\n"));
	//return (startswith(s, "||")
	//		|| startswith(s, "&")
	//		|| startswith(s, "&&")
	//		|| startswith(s, ";")
	//		|| startswith(s, "(")
	//		|| startswith(s, ")")
	//		|| startswith(s, ";;")
	//		|| startswith(s, "|")
	//		|| startswith(s, "\n"));
}

bool	is_variable(const char *s)
{
	return (*s == '$' && is_alpha_under(s[1]));
}

/*
Special Parameters
	   The shell treats several parameters specially.  These parameters may
	   only be referenced; assignment to them is not allowed.
	   *	Expands to the positional parameters, starting from one.  When the
			expansion occurs within double quotes, it expands to a single word
			with the value of each parameter separated by the first character
			of the IFS special variable.  That is, "$*" is equivalent to
			"$1c$2c...", where c is the first character of the value of the IFS
			variable.  If IFS is unset, the parameters are separated by spaces.
			If IFS is null, the parameters are joined without intervening
			separators.
	   @	Expands to the positional parameters, starting from one.  When
			the expansion occurs within double quotes, each parameter expands
			to a separate word.  That is, "$@" is equivalent to "$1" "$2" ...
			If the double-quoted expansion occurs within a word, the expansion
			of the first parameter is joined with the beginning part of the
			original word, and the expansion of the last parameter is joined
			with the last part of the original word.  When there are no
			positional parameters, "$@" and $@ expand to nothing (i.e., they
			are removed).
       #	Expands to the number of positional parameters in decimal.
	   ?	Expands to the status of the most recently executed foreground
	   		pipeline.
	   -	Expands to the current option flags as specified upon invocation,
			by the set builtin command, or those set by the shell itself (such
			as the -i option).
	   $	Expands to the process ID of the shell.  In a () subshell, it
	   		expands to the process ID of the current shell, not the subshell.
	   !	Expands to the process ID of the most recently executed background
	   		(asynchronous) command.
	   0    Expands to the name of the shell or shell script.  This is set at
			shell initialization.  If bash is invoked with a file of commands,
			$0 is set to the name of that file.  If bash is started with the -c
			option, then $0 is set to the first argument after the string to be
			executed, if one is present.  Otherwise, it is set to the file name
			used to invoke bash, as given by argument zero.
	   _	At shell startup, set to the absolute pathname used to invoke the
			shell or shell script being executed as passed in the environment
			or argument list.  Subsequently, expands to the last argument to
			the previous command, after expansion.  Also set to the full
			pathname used to invoke each command executed and placed in the
			environment exported to that command.  When checking mail, this
			parameter holds the name of the mail file currently being checked.
*/
bool	is_specialchr(char c)
{
	return (strchr("?", c));
	//return (strchr("*@#?-$!0_", s[1]));
}

bool	is_special_param(const char *s)
{
	return (*s == '$' && is_specialchr(s[1]));
}

bool	is_unquoted(const char *s)
{
	return (*s != '\"'
		&& *s != '\''
		&& !is_metachr(*s)
		&& !is_variable(s)
		&& !is_control_operator(s));
}

bool	is_number(const char *s)
{
	if (!isdigit(*s))
		return (false);
	while (isdigit(*s))
		s++;
	return (is_blank(*s) || is_metachr(*s) || is_control_operator(s));
}

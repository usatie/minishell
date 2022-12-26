/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:24:32 by susami            #+#    #+#             */
/*   Updated: 2022/12/26 15:18:20 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
PARAMETERS
	A parameter is an entity that stores values.  It can be a name, a number,
	or one of the special characters listed below under Special Parameters.  A
	variable is a parameter denoted by a name.  A variable has a value and zero
	or more attributes.  Attributes are assigned using the declare builtin
	command (see declare below in SHELL BUILTIN COMMANDS).

	A parameter is set if it has been assigned a value.  The null string is a
	valid value.  Once a variable is set, it may be unset only by using the
	unset builtin command (see SHELL BUILTIN COMMANDS below).

	A variable may be assigned to by a statement of the form

	name=[value]

	If value is not given, the variable is assigned the null string.  All
	values undergo tilde expansion, parameter and variable expansion, command
	substitution, arithmetic expansion, and quote removal (see EXPANSION
	below).  If the variable has its integer attribute set, then value is
	evaluated as an arithmetic expression even if the $((...)) expansion is not
	used (see Arithmetic Expansion below).  Word splitting is not performed,
	with the exception of "$@" as explained below under Special Parameters.
	Pathname expansion is not performed.  Assignment statements may also appear
	as arguments to the alias, declare, typeset, export, readonly, and local
	builtin commands.

	In the context where an assignment statement is assigning a value to a
	shell variable or array index, the += operator can be used to append to or
	add to the variable's previous value.  When += is applied to a variable for
	which the integer attribute has been set, value is evaluated as an
	arithmetic expression and added to the variable's current value, which is
	also evaluated.  When += is applied to an array variable using compound
	assignment (see Arrays below), the variable's value is not unset (as it is
	when using =), and new values are appended to the array beginning at one
	greater than the array's maximum index.  When applied to a string-valued
	variable, value is expanded and appended to the variable's value.
*/
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

// * @ # ? - $ ! 0 _
bool	is_specialchr(char c)
{
	return (ft_strchr("?", c));
}

bool	is_special_param(const char *s)
{
	return (*s == '$' && is_specialchr(s[1]));
}

bool	is_plain_text(const char *s)
{
	return (*s != '\"'
		&& *s != '\''
		&& !is_variable(s)
		&& !is_special_param(s)
		&& !is_metachr(*s));
}

bool	is_number(const char *s)
{
	if (!ft_isdigit(*s))
		return (false);
	while (ft_isdigit(*s))
		s++;
	return (is_blank(*s) || is_metachr(*s) || is_control_operator(s));
}

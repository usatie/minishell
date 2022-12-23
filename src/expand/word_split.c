/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:11:13 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 13:20:04 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
   Word Splitting
	   The shell scans the results of parameter expansion, command
	   substitution, and arithmetic expansion that did not occur within double
	   quotes for word splitting.

	   The shell treats each character of IFS as a delimiter, and splits the
	   results of the other expansions into words on these characters.  If IFS
	   is unset, or its value is exactly <space><tab><newline>, the default,
	   then any sequence of IFS characters serves to delimit words.  If IFS has
	   a value other than the default, then sequences of the whitespace
	   characters space and tab are ignored at the beginning and end of the
	   word, as long as the whitespace character is in the value of IFS (an IFS
	   whitespace character).  Any character in IFS that is not IFS whitespace,
	   along with any adjacent IFS whitespace characters, delimits a field.  A
	   sequence of IFS whitespace characters is also treated as a delimiter.
	   If the value of IFS is null, no word splitting occurs.

	   Explicit null arguments ("" or '') are retained.  Unquoted implicit null
	   arguments, resulting from the expansion of parameters that have no
	   values, are removed.  If a parameter with no value is expanded within
	   double quotes, a null argument results and is retained.

	   Note that if no expansion occurs, no splitting is performed.
*/

void	word_split(t_node *node)
{
	(void)node;
}

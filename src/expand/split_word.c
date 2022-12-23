/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 13:11:13 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 15:43:49 by susami           ###   ########.fr       */
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
	// node    -> str -> str -> str
	// |          value  value  value
	// node    -> str -> str -> str
	// |||        value  value  value
	// node    -> str -> str -> str
	// |          value  value  value
	// node    -> str -> str -> str
	//            value  value  value
	//
	// node    -> str
	//         -> str -> str -> str
	// node    -> str
	// node    -> str
	// node    -> str
	//
	// foo="a   b   c"
	// echo $foo
	// echo $foo$foo
	// echo $foo" "$foo
	// 
	//
	// ND_CMD args -> ND_WORD str -> STR_VAR ("$foo")
	// ND_CMD args -> ND_WORD str -> STR_PLAIN str ("a")
	//                |-> ND_WORD str -> STR_PLAIN str ("b")
	//                |-> ND_WORD str -> STR_PLAIN str ("c")
	//
	// ND_CMD args -> ND_WORD str -> STR_VAR ("$foo") -> STR_VAR ("$foo")
	// ND_CMD args -> ND_WORD str -> STR_PLAIN str ("a")
	//                |-> ND_WORD str -> STR_PLAIN str ("b")
	//                |-> ND_WORD str -> STR_PLAIN str ("c") -> STR_PLAIN str ("a")
	//                |-> ND_WORD str -> STR_PLAIN str ("b")
	//                |-> ND_WORD str -> STR_PLAIN str ("c")
	//
	// ND_CMD args -> ND_WORD str -> STR_VAR ("$foo") -> STR_DOUBLE (" ") -> STR_VAR ("$foo")
	// ND_CMD args -> ND_WORD str -> STR_PLAIN str ("a")
	//                |-> ND_WORD str -> STR_PLAIN str ("b")
	//                |-> ND_WORD str -> STR_PLAIN str ("c")
	//                |-> ND_WORD str -> STR_PLAIN str ("a")
	//                |-> ND_WORD str -> STR_PLAIN str ("b")
	//                |-> ND_WORD str -> STR_PLAIN str ("c")
	// IFS -> append new node
	// t_str -> append new str

void	internal_split_word(t_node *word);

void	split_word(t_node *node)
{
	if (!node)
		return ;
	if (node->kind == ND_WORD)
		internal_split_word(node);
	split_word(node->rhs);
	split_word(node->lhs);
	split_word(node->args);
	split_word(node->redirects);
	split_word(node->next);
}

static const char	*ifs = " \t\n";

static bool	is_ifs(char c, const char *ifs)
{
	return (ft_strchr(ifs, c) != NULL);
}

// Read until next ifs
t_str	*ws_plain_text(char **rest, char *line)
{
	t_str	*str;
	char	*start;

	start = line;
	while (*line != '\0' && is_ifs(*line, ifs))
		line++;
	str = new_str(STR_PLAIN, start, line - start, NULL);
	*rest = line;
	return (str);
}
// "a   b"
// args ND_WORD1 -> ND_WORD2 -> ND_WORD3
//      ND_WORD1 -> new_node -> ND_WORD2 -> ND_WORD3
// insert_to_next
//
// strs STR_PLAIN1 -> STR_PLAIN2
// strs STR_PLAIN1 -> STR_PLAIN2 -> new_str
// add_str_back

void	insert_to_next(t_node *node, t_node *new_node)
{
	new_node->next = node->next;
	node->next = new_node;
}

void	internal_split_word(t_node *word)
{
	t_node	*node;
	t_str	*s;
	t_str	*new;
	bool	seen_ifs;
	char	*p;

	node = new_node(ND_WORD, NULL);
	seen_ifs = true;
	s = word->str;
	// $foo" "$foo
	while (s)
	{
		// "a  b"
		if (s->kind == STR_PLAIN || s->kind == STR_DOUBLE || s->kind == STR_SINGLE)
			node->str = add_str_back(node->str, dup(s));
		else if (s->kind == STR_VAR || s->kind == STR_SPECIAL_PARAM)
		{
			p = s->value;
			while (*p)
			{
				if (consume_ifs(&p, p))
					continue;
				cur->next = ws_plain_text(&p, p);
				cur = cur->next;
			}
		}
		s = s->next;
	}
	free_str(word->str);
	//free_node(word);
}

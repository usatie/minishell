/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:35:03 by susami            #+#    #+#             */
/*   Updated: 2022/12/23 13:18:40 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>
#include "libft.h"
#include "minishell.h"

bool	is_parameter(char *line)
{
	return (is_special_param(line) || is_variable(line));
}

t_str	*non_parameter_plain_text(char **rest, char *line)
{
	char	*start;

	start = line;
	while (*line && !is_parameter(line))
		line++;
	*rest = line;
	return (new_str(STR_PLAIN, start, line - start, NULL));
}

t_str	*line_to_str(char *line)
{
	t_str	head;
	t_str	*s;

	s = &head;
	while (*line)
	{
		// Special Parameter
		if (is_special_param(line))
			s->next = special_parameter(&line, line);
		// Parameter
		else if (is_variable(line))
			s->next = variable(&line, line);
		// Non parameter plain text
		else
			s->next = non_parameter_plain_text(&line, line);
		s = s->next;
	}
	return (head.next);
}

char	*expand_line(char *line)
{
	t_str	*str;

	str = line_to_str(line);
	expand_parameter_str(str);
	return (str_to_word(str, true));
}

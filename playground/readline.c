/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:23:43 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/01 14:26:40 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>

int	main(void)
{
	char	*hoge;
	char	*line;

	hoge = "minishell $ ";
	line = readline(hoge);
	printf("%s\n", line);
}

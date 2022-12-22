/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susami <susami@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:55:55 by susami            #+#    #+#             */
/*   Updated: 2022/12/22 23:56:21 by susami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	ft_execvp(char *file, char *argv[])
{
	char	*path;

	// Empty command
	if (file == NULL)
		exit(0);
	// Builtin
	if (isbuiltin(file))
	{
		exec_builtin(argv);
		exit(0);
	}
	path = search_path(file);
	// No such file
	if (path == NULL)
		err_exit(file);
	// Execute
	execve(path, argv, environ);
	fatal_exit("execve");
}

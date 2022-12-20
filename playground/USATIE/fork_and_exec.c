/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:35:34 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/20 17:02:10 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <string.h>

int	main(int agvc, char *argv[])
{
	int			status;
	pid_t		pid;
	extern char **environ;

	pid	= fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		argv[0] = "echo";
		argv[1] = "hello World";
		argv[2] = NULL;
		execve("/bin/echo", argv, environ);
		perror("execve");
		exit(0);
	}
	else 
	{
		printf("Im parent");
	}
	return (0);
}



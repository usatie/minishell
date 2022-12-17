/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkunimot <hatopopo142@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:09:03 by mkunimot          #+#    #+#             */
/*   Updated: 2022/12/17 15:33:14 by mkunimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	wait_status(int st)
{
	printf("子プロセスが正常終了           WIFEXITED   :%d\n", WIFEXITED(st));
	printf("子プロセスの終了status         WEXITSTATUS :%d\n", WEXITSTATUS(st));
	printf("子プロセスがsignalにより終了   WIFSIGNALED :%d\n", WIFSIGNALED(st));
	printf("->子プロセス終了の原因のsignal WTERMSIG    :%d\n", WTERMSIG(st));
}

int	main(void)
{
	pid_t	pid;
	pid_t	ret_wait;
	int		status;

	status = 0;
	pid = fork();

	if (pid == 0)
	{
		printf("child pid  :%d\n", pid);
		exit(1);
	}
	else
	{
		printf("parent pid :%d\n", pid);
	}
	ret_wait = wait(&status);
	printf("ret_wait :%d\n", ret_wait);
	wait_status(status);
	printf ("%d %s\n", status >> 8, "finish");
}

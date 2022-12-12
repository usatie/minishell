#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		printf("child %d\n", pid);
		exit(1);
	}
	else
	{
		printf("oya %d\n", pid);
	}
	wait(&status);
	printf("%d %s\n", status >> 8, "finish");
}

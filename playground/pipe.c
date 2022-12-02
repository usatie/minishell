#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int fd[2];

	int err = pipe(fd);
	printf("fd[0] = %d fd[1] = %d ,err = %d", fd[0], fd[1], err);
}
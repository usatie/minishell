#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int	main(void)
{
	int	fd;
	
	fd = open("output.txt", O_WRONLY);
	if (fd < 0)
		exit(1);
	/*
	if (close(STDOUT_FILENO) < 0)
		exit(1);
	if (dup(fd) < 0)
		exit(1);
	*/
	dup2(fd, STDOUT_FILENO);
	close(fd);
	printf("hello world\n");
	exit(EXIT_SUCCESS);
}


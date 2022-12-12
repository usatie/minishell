#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	mysystem(const char *command)
{
	char *const argv[5] = {"sh", "-c", (char *)command, NULL};
	execve("/bin/sh", argv, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	int	exit_status;

	exit_status = mysystem(argv[1]);
	// printf("%d\n", exit_status >> 8);
	return (exit_status);
}

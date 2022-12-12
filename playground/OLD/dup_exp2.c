#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int	fd;

	
	fd = dup(STDOUT_FILENO);
	printf("STDOUT_FILENO: %d, fd: %d\n", STDOUT_FILENO, fd);
	if (write(1, "hello from stdout\n", 18) < 0)
		printf("Error\n");
	if (write(fd, "hello from dup fd\n", 18) < 0)
		printf("Error\n");
	close(1);
	printf("hello from printf\n");
	dprintf(3, "hello from dprintf\n");
	exit(EXIT_SUCCESS);
}

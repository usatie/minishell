#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int	status;
	switch (fork()) {
		case -1:
			// error
			printf("fork() error\n");
			exit(1);
		case 0:
			// child
			execve("/bin/ls", NULL, NULL);
			printf("execve() error\n");
			exit(1);
		default:
			// parent
			break;
	}
	wait(&status);
	printf("status = %d\n", status >> 8);
}

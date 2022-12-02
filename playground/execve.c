#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char *argv[3];
	argv[0] = ".";
	argv[1] = "-la";
	argv[2] = NULL;

	execve("/bin/ls", argv, NULL);
	printf("This message will not be printed.\n");
}

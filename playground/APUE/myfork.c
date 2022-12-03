#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		globvar = 6;


int	main(void)
{
	int		var;
	pid_t	pid;
	size_t	len;
	char	buf[] = "a write to stdout\n";

	var = 88;
	printf("buf = %s", buf);
	printf("sizeof_buf = %lu\n", sizeof(buf));
	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
	{
		printf("Error!\n");
		exit(2);
	}
	char *Thread;

	// make child process
	pid = fork();
	if (pid < 0)
	{
		printf("fork error!\n");
		exit(2);
	}
	else if (pid == 0)
	{
		Thread = "child";
		globvar++;
		var++;
	}
	else
	{
		Thread = "parent";
		sleep(2);
	}
	printf("\n[%s]\n",Thread);
	printf("Thread's pid       : %5d\n", pid);
	printf("caller process pid : %ld\n", (long)getpid());
	printf("parents pid        : %ld\n", (long)getppid());
	printf("globvar            : %5d\n", globvar);
	printf("var                : %5d\n", var);
	exit(0);
}

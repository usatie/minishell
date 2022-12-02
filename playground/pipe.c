#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int fd[2];

	int err = pipe(fd);

	printf("fd[0] = %d fd[1] = %d ,err = %d\n\n", fd[0], fd[1], err);

	int ret = write(fd[0], "hello", 5);
	printf("fd[0] : %d errno : %d\n", ret, errno);
	ret = write(fd[1], "world", 5);
	printf("fd[1] : %d\n", ret);
	errno = 0;

	char buf[100];

	ret = read(fd[0], buf, 99);
	if (ret < 0)
		exit(1);
	buf[ret] = '\0';
	printf("fd[0] : %d errno : %d\n", ret, errno);
	printf("buf : %s\n", buf);

	// ret = read(fd[1], buf, 99);
	// printf("fd[1] : %d errn : %d\n", ret, errno);
}
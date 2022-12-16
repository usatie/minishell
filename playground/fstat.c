#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>

int	main(void)
{
	struct stat	st;
	int			ret;

	for (int fd = -1; fd < 5; fd++)
	{
		errno = 0;
		ret = fstat(fd, &st);
		printf("fd = %i, ret = %d, errno = %d\n", fd, ret, errno);
	}
}

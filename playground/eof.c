#include <unistd.h>
#define BUFSIZE 128
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	is_valid(int fd)
{
	errno = 0;
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

int	main(void)
{
	char	buf[BUFSIZE];
	int 	rc;

	printf("start is_valid = %d\n", is_valid(STDIN_FILENO));
	setvbuf(stdin, NULL, _IOLBF, 0);
	while (1)
	{
		rc = read(STDIN_FILENO, buf, BUFSIZE-1);
		printf("rc = %d\n", rc);
		if (rc <= 0)
			break;
		if (buf[rc-1] == '\n')
			rc--;
		buf[rc] = '\0';
		write(STDOUT_FILENO, "[", 1);
		write(STDOUT_FILENO, buf, rc);
		write(STDOUT_FILENO, "]\n", 2);
	}
	printf("end is_valid = %d\n", is_valid(STDIN_FILENO));
}

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int	main(void)
{
	chdir("/etc");
	system("pwd");

	int	fd = open("/etc", O_RDONLY);
	fchdir(fd);
	system("pwd");
}

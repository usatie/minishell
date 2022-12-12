#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	/*
	 ssize_t
     read(int fildes, void *buf, size_t nbyte);
	*/
	int		fd;
	char	buf[10];

	/*
	buf[0] = 'h';
	buf[1] = 'e';
	buf[2] = 'l';
	buf[3] = 'l';
	buf[4] = 'o';
	buf[5] = '\0';

	printf("[%s]\n", buf);
	for (int i = 0; i < 10; i++)
		printf("%d: %d\n", i, (char)buf[i]);
		*/
	fd = open("read.c", O_RDONLY);
	int ret = read(fd, buf, 10);
	printf("ret = %d\n", ret);
	if (ret < 0)
		printf("Error\n");
	else
	{
		//buf[ret] = '\0';
		printf("buf: [%s]\n", buf);
	}
}

void putstr(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}




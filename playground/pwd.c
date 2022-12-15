#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>

void	print_filetype(struct stat *buf)
{
	//if ((buf->st_mode & S_IFMT) == S_IFREG)
	if (S_ISREG(buf->st_mode))
		printf("    Regular file\n");
	else if (S_ISDIR(buf->st_mode))
		printf("    Directory\n");
	else if (S_ISCHR(buf->st_mode))
		printf("    Character device\n");
	else if (S_ISBLK(buf->st_mode))
		printf("    Block device\n");
	else if (S_ISFIFO(buf->st_mode))
		printf("    FIFO or pipe\n");
	else if (S_ISSOCK(buf->st_mode))
		printf("    Socket\n");
	else if (S_ISLNK(buf->st_mode))
		printf("    Symbolic link\n");
	else
		printf("    Unknown file type\n");
}

void	print_stat(struct stat *buf)
{
	printf("  st_dev: %d\n", buf->st_dev);
	/*
	printf("    Device containing i-node: major=%ld, minor=%ld\n",
			(long) major(buf->st_dev), (long) minor(buf->st_dev));
	*/
	printf("  st_ino: %llu\n", buf->st_ino);
	printf("  st_mode: %o\n", buf->st_mode);
	print_filetype(buf);
	if (buf->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
		printf("    special bits set:    %s%s%s\n",
				(buf->st_mode & S_ISUID) ? "set-UID " : "",
				(buf->st_mode & S_ISGID) ? "set-GID " : "",
				(buf->st_mode & S_ISVTX) ? "sticky " : "");
	printf("  st_nlink: %d\n", buf->st_nlink);
	printf("  st_uid: %d\n", buf->st_uid);
	printf("  st_gid: %d\n", buf->st_gid);
	printf("  st_rdev: %d\n", buf->st_rdev);
	/*
	if (S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))
		printf("    Device number (st_rdev): major=%ld, minor=%ld\n",
				(long) major(buf->st_rdev), (long) minor(buf->st_rdev));
	*/
	/*
	printf("  st_size: %llu\n", buf->st_size);
	printf("  st_blksize: %d\n", buf->st_blksize);
	printf("  st_blocks: %lld\n", buf->st_blocks);
	printf("  st_atime: %ld\n", buf->st_atime);
	printf("    Last file Access       : %s", ctime(&buf->st_atime));
	printf("  st_mtime: %ld\n", buf->st_mtime);
	printf("    Last file Modification : %s", ctime(&buf->st_mtime));
	printf("  st_ctime: %ld\n", buf->st_ctime);
	printf("    Last status Change     : %s", ctime(&buf->st_ctime));
	printf("  st_birthtime: %ld\n", buf->st_birthtime);
	printf("    File Creation Time     : %s", ctime(&buf->st_birthtime));
	*/
}

int	main(void)
{
	char	buf[PATH_MAX];
	struct stat	stat;
	int	cwdfd;

	cwdfd = open(".", O_RDONLY);	
	chdir("/etc");
	printf("%s\n", getcwd(buf, PATH_MAX));

	printf(".\n");
	lstat(".", &stat);
	print_stat(&stat);

	printf("..\n");
	lstat("..", &stat);
	print_stat(&stat);

	printf("/etc\n");
	lstat("/etc", &stat);
	print_stat(&stat);

	printf("/private/etc\n");
	lstat("/private/etc", &stat);
	print_stat(&stat);

	fchdir(cwdfd);
	close(cwdfd);
}

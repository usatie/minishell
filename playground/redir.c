#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

// gcc redir.c && ./a.out && tail -n +1 *.txt

/*
   REDIRECTION
	   Before a command is executed, its input and output may be redirected
	   using a special notation interpreted by the shell.  Redirection may also
	   be used to open and close files for the current shell execution
	   environment.  The following redirection operators may precede or appear
	   anywhere within a simple command or may follow a command.  Redirections
	   are processed in the order they appear, from left to right.

	   In the following descriptions, if the file descriptor number is omitted,
	   and the first character of the redirection operator is <, the
	   redirection refers to the standard input (file descriptor 0).  If the
	   first character of the redirection operator is >, the redirection refers
	   to the standard output (file descriptor 1).

	   The word following the redirection operator in the following
	   descriptions, unless otherwise noted, is subjected to brace expansion,
	   tilde expansion, parameter expansion, command substitution, arithmetic
	   expansion, quote removal, pathname expansion, and word splitting.  If it
	   expands to more than one word, bash reports an error.

	   Note that the order of redirections is significant.  For example, the
	   command

	   ls > dirlist 2>&1

	   directs both standard output and standard error to the file dirlist,
	   while the command

	   ls 2>&1 > dirlist

	   directs only the standard output to file dirlist, because the standard
	   error was duplicated as standard output before the standard output was
	   redirected to dirlist.
	   
	   ...
	   A failure to open or create a file causes the redirection to fail.

	   Redirections using file descriptors greater than 9 should be used with
	   care, as they may conflict with file descriptors the shell uses
	   internally.
*/

void	writes(void)
{
	char	buf[] = "x is being written\n";

	for (int i = 0; i < 5; i++)
	{
		buf[0] = '0' + i;
		errno = 0;
		if (write(i, buf, sizeof(buf)) < 0)
			perror("write");
	}
}

/*
   Redirecting Output
	   Redirection of output causes the file whose name results from the
	   expansion of word to be opened for writing on file descriptor n, or the
	   standard output (file descriptor 1) if n is not specified.  If the file
	   does not exist it is created; if it does exist it is truncated to zero
	   size.

	   The general format for redirecting output is:

	   [n]>word

	   If the redirection operator is >, and the noclobber option to the set
	   builtin has been enabled, the redirection will fail if the file whose
	   name results from the expansion of word exists and is a regular file.
	   If the redirection operator is >|, or the redirection operator is > and
	   the noclobber option to the set builtin command is not enabled, the
	   redirection is attempted even if the file named by word exists.
*/

// 0>zero.txt 1>one.txt 2>two.txt 3>three.txt 4>four.txt
int	stashfd[5] = {-1, -1, -1, -1, -1};
int	dstfds[5] = {-1, -1, -1, -1, -1};

bool	is_valid_fd(int fd)
{
	errno = 0;
	if (fcntl(fd, F_GETFD) == -1 && errno == EBADF)
		return (false);
	return (true);
}
void	redirect(void)
{
	char	*paths[] = {"zero.txt", "one.txt", "two.txt", "three.txt",
		"four.txt"};
	for (int i = 0; i < 5; i++)
	{
		char	*path = paths[i];
		/* Implementation 1
		 * srcfdが有効なfdだった場合、execの終了後にリダイレクトを終えて
		 * 元のsrcfdの指すファイルに戻せるようにしておきたい
		if (srcfd is valid)
			stashfd[i] = dup(srcfd);
		// ここでdupすると、dstfd=3, stashfd[0]=4 とかなってしまって、srcfd=4
		// をredirectする時におかしなことになってしまう・・・
		// しかしsrcfdを保存しておきたい時にどこに保存しておけば・・・？
		// それがもしかして10以降のfd...!?
		*/
		/* Implementation 2
		 * fdを10個（以上）ずらしたところに一時的に退避させておく
		if (srcfd is valid)
			int tmpfd = 10 + srcfd;
			while (tmpfd is valid)
				tmpfd++;
			stashfd[i] = dup2(srcfd, tmpfd);
		*/
		int	srcfd = i;
		if (is_valid_fd(srcfd))
		{
			int	tmpfd = 10 + srcfd;
			while (is_valid_fd(tmpfd))
				tmpfd++;
			stashfd[i] = dup2(srcfd, tmpfd);
		}
		int	dstfd = open(path, O_CREAT | O_WRONLY, 0644);
		dstfds[i] = dstfd;
		if (dstfd != srcfd)
		{
			dstfds[i] = dup2(dstfd, srcfd);
			close(dstfd);
		}
	}
}

void	restore_redirect(void)
{
	for (int i = 0; i < 5; i++)
	{
		int	tmpfd = stashfd[i];
		int	dstfd = dstfds[i];
		if (tmpfd < 0)
		{
			close(dstfd);
			continue ;
		}
		if (dstfd != tmpfd)
		{
			dup2(tmpfd, dstfd);
			close(tmpfd);
		}
	}
}

int	main(void)
{
	redirect();
	writes();
	for (int i = 0; i < 5; i++)
	{
		printf("stashfd[%d] = %d\n", i, stashfd[i]);
		printf("dstfd[%d] = %d\n", i, dstfds[i]);
	}
	fflush(stdout); // これがないと、restoreした後にflushされることになってしまう
	restore_redirect();
	writes();
}

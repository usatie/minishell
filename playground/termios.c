#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

void	unset_echoctl(void)
{
	struct termios	tp;
	int				ttyfd;

	if (tcgetattr(STDIN_FILENO, &tp) == 0)
		ttyfd = STDIN_FILENO;
	else if (tcgetattr(STDOUT_FILENO, &tp) == 0)
		ttyfd = STDOUT_FILENO;
	else if (tcgetattr(STDERR_FILENO, &tp) == 0)
		ttyfd = STDERR_FILENO;
	else
		return ;
	tp.c_lflag &= ~ECHOCTL;
	tcsetattr(ttyfd, TCSAFLUSH, &tp);
}

void	set_echoctl(void)
{
	struct termios	tp;
	int				ttyfd;

	if (tcgetattr(STDIN_FILENO, &tp) == 0)
		ttyfd = STDIN_FILENO;
	else if (tcgetattr(STDOUT_FILENO, &tp) == 0)
		ttyfd = STDOUT_FILENO;
	else if (tcgetattr(STDERR_FILENO, &tp) == 0)
		ttyfd = STDERR_FILENO;
	else
		return ;
	tp.c_lflag |= ECHOCTL;
	tcsetattr(ttyfd, TCSAFLUSH, &tp);
}

int	main(void)
{
	//unset_echoctl();
	set_echoctl();
}

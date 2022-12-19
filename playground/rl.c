#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>
#define PROMPT "minishell$ cat <<EOF\n"

static volatile sig_atomic_t	sig = 0;
int	interrupted = 0;

int	check_state(void)
{
	//printf("check_state: sig = %d, eof = %d\n", sig, rl_eof_found);
	if (sig == 1)
	{
		sig = 0;
		interrupted = 1;
		rl_done = 1;
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay(); // Refresh the prompt
	}
	int result, nread;
	errno = 0;
	result = ioctl(STDIN_FILENO, FIONREAD, &nread);
	printf("check_state: result = %d, nread = %d, errno = %d\n", result, nread, errno);
	if (errno)
		perror("ioctl error");
	return (0);
}

void	handler(int signum)
{
	sig = 1;
	(void)signum;
		interrupted = 1;
		rl_done = 1;
		rl_on_new_line(); // Regenerate the prompt on a newline
		rl_replace_line("", 0); // Clear the previous text
		rl_redisplay(); // Refresh the prompt
		close(STDIN_FILENO);
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_mask = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	setup_readline(void)
{
	rl_outstream = stderr;
	//rl_event_hook = check_state;
}

#define BUFSIZE 1024
int	main(void)
{
	char	*line = NULL;
	char	buf[BUFSIZE] = {};
	int		stashfd;

	stashfd = dup(STDIN_FILENO);
	// Setup
	setup_readline();
	setup_signal();

	// REPL
	while (1)
	{
		if (line)
			strlcat(buf, "\n", BUFSIZE);
		line = readline("> ");
		printf("[%s]", line);
		if (!line)
		{
			break;
		}
		if (interrupted)
			break;
		if (strcmp(line, "EOF") == 0)
			break;
		strlcat(buf, line, BUFSIZE);
	}
	dup2(stashfd, STDIN_FILENO);
	close(stashfd);
	if (!interrupted)
		printf("%s", buf);
	printf("<exit>\n");
	return (0);
}

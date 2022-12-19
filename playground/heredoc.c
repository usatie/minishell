#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>

int	cat(void)
{
	pid_t	pid;
	int		status;
	char	*argv[] = {"cat", NULL};

	pid = fork();
	if (pid == 0)
		execve("/bin/cat", argv, NULL);
	waitpid(pid, &status, 0);
	return (status);
}

// Stash STDIN_FILENO to tmpfd
int	tmpfd = -1;
int	pfd[2] = {-1, -1};
int	interrupted = 0;

void	read_heredoc(char *delimiter)
{
	char	*line;
	int		stashstdin;

	stashstdin = dup(STDIN_FILENO);
	pipe(pfd);
	line = NULL;
	while (1)
	{
		if (line)
			write(pfd[1], "\n", 1);
		interrupted = 0;
		line = readline("> ");
		if (interrupted)
			break;
		if (!line)
			break;
		if (strcmp(delimiter, line) == 0)
			break;
		write(pfd[1], line, strlen(line));
		free(line);
	}
	dup2(stashstdin, STDIN_FILENO);
	close(stashstdin);
	close(pfd[1]);
	pfd[1] = -1;
}

void	redirect_heredoc(void)
{
	// Redirect pipe read end to STDIN_FILENO
	// Stash STDIN_FILENO to tmpfd
	tmpfd = STDIN_FILENO + 10;
	tmpfd = dup2(STDIN_FILENO, tmpfd);
	// Duplicate pipe read end to STDIN_FILENO
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	pfd[0] = -1;
}

void	restore_redirect(void)
{
	// restore STDIN_FILENO
	dup2(tmpfd, STDIN_FILENO);
	// tmpfd(duplicated STDIN_FILENO) is no more needed
	close(tmpfd);
}

#include <termios.h>
void	setup_term(void)
{
	struct termios tp;

	if (tcgetattr(STDIN_FILENO, &tp) == -1)
		return ;
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
		return ;
}

#include <signal.h>
void	handler(int signum)
{
	//sig = 1;
	(void)signum;
	rl_done = 1;
	close(STDIN_FILENO);
	interrupted = 1;
	setup_term();
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
}

#define PROMPT "minishell$ cat <<EOF\n"
int	main(void)
{
	int	cnt = 0;
	int	status;

	setup_readline();
	setup_signal();
	setup_term();

	while (cnt < 5)
	{
		status = 0;
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		read_heredoc("EOF");
		redirect_heredoc();
		if (!interrupted)
			status = cat();
		interrupted = 0;
		restore_redirect();
		cnt++;
	}
	return (status);
}

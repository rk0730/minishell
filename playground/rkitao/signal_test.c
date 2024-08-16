# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>

void	sigint_handler_parent(int sig)
{
	printf("Caught signal in parent: %d\n", sig);
}

void	sigint_handler_child(int sig)
{
	printf("Caught signal in child: %d\n", sig);
}


int	main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_child);
		printf("I'm the child process %d\n", pid);
		while (1);
	}
	else
	{
		wait(NULL);
		signal(SIGINT, sigint_handler_parent);
		printf("I'm the parent process %d\n", pid);
	}
}

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>

sig_atomic_t g_signum = 0;

void	sigquit_handler(int sig)
{
	g_signum = sig;
	// rl_redisplay();
}

void	sigquit_handler_child(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

int	main(void)
{
	char	*line;
	pid_t	pid;

	while (1)
	{
		g_signum = 0;
		line = readline("prompt> ");
		if (!line)
			break ;
		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			signal(SIGQUIT, sigquit_handler_child);
			printf("exec: %s\n", line);
			if (strlen(line) == 0)
				exit(EXIT_SUCCESS);
			char *argv[] = {"sleep", "3", NULL};
			execve("/usr/bin/sleep", argv, NULL);
			exit(EXIT_SUCCESS);
		}
		else
		{
			signal(SIGQUIT, sigquit_handler);
			waitpid(pid, NULL, 0);
			if (g_signum == SIGQUIT)
			{
				// printf("Quit");
			}
		}

		add_history(line);
		free(line);
	}
}

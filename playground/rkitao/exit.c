#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int	main(void)
{
	int status;
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		// 子プロセス
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		char *execve_argv[] = {"/usr/bin/cat", NULL};
		execve("/usr/bin/cat", execve_argv, NULL);
		// exit(1);
	}
	else
	{
		// 親プロセス
		// 子プロセスの終了を待つ
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		wait(&status);
		printf("status: %d\n", status);
		printf("WEXITSTATUS(status): %d\n", WEXITSTATUS(status));
	}
	if (status == 0)
		exit(EXIT_SUCCESS);
	else
		exit(status + 128);
}

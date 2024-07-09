#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
		exit(1);
	}
	else
	{
		// 親プロセス
		// 子プロセスの終了を待つ
		wait(&status);
		printf("status: %d\n", status);
		printf("WEXITSTATUS(status): %d\n", WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}

// forkした子プロセスで配列をいじってもぺつプロセスなので親プロセスに影響はない（アドレスは同じっぽいが並列で別物として処理しているのかな？）

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(void)
{
	pid_t pid;
	int array[3];
	array[0] = 0;
	array[1] = 1;
	array[2] = 2;
	pid = fork();
	if (pid == 0)
	{
		printf("child %p\n", array);
		array[0] = 42;
		array[1] = 43;
		array[2] = 44;
		printf("array[0]: %d\n", array[0]);
		printf("array[1]: %d\n", array[1]);
		printf("array[2]: %d\n", array[2]);
	}
	else
	{
		wait(NULL);
		printf("parent %p\n", array);
		printf("array[0]: %d\n", array[0]);
		printf("array[1]: %d\n", array[1]);
		printf("array[2]: %d\n", array[2]);
	}
}
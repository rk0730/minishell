#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


// ls | grep docker | wc | wc

void recursive(char ***cmd_list, int index, int pipe_fd[4]) {
	pid_t pid;
	pid_t pid2;

	if (index == 0) {
		close(pipe_fd[0]);
		pid = fork();
		if (pid == 0) {
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			execve(cmd_list[index][0], cmd_list[index], NULL);
		} else {
			close(pipe_fd[1]);
			waitpid(pid, NULL, 0);
		}
	} else {
		pipe(pipe_fd + 2);
		pid = fork();
		if (pid == 0) {
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			pipe_fd[0] = pipe_fd[2];
			pipe_fd[1] = pipe_fd[3];
			recursive(cmd_list, index - 1, pipe_fd);
		} else {
			close(pipe_fd[0]);
			close(pipe_fd[3]);
			pid2 = fork();
			if (pid2 == 0) {
				dup2(pipe_fd[2], STDIN_FILENO);
				close(pipe_fd[2]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				execve(cmd_list[index][0], cmd_list[index], NULL);
			} else {
				close(pipe_fd[2]);
				close(pipe_fd[1]);
				waitpid(pid2, NULL, 0);
			}
		}
	}
}	

int	exec_pipe(char ***cmd_list, int index) {
	int pipe_fd[4];
	pid_t pid;
	pid_t pid2;
	int status;

	if (index == 0) {
		
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0) {
		//再帰
		recursive(cmd_list, index - 1, pipe_fd);
		exit(0);
	} else {
		//親プロセス
		//最後のコマンドを実行する
		close(pipe_fd[1]);
		pid2 = fork();
		if (pid2 == 0) {
			// wc
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			if (execve(cmd_list[index][0], cmd_list[index], NULL) == -1) {
				fprintf(stderr, "execve %s\n", cmd_list[index][0]);
				exit(1);
			}
		} else {
			close(pipe_fd[0]);
			waitpid(pid2, &status, 0);
		}
		waitpid(pid, NULL, 0);
		return WEXITSTATUS(status);
	}
}

char ***set_cmd_list(){
	char ***cmd_list = malloc(2 * sizeof(char**));

	cmd_list[0] = malloc(2 * sizeof(char*));
	cmd_list[0][0] = strdup("/bin/cat");
	cmd_list[0][1] = NULL;

	cmd_list[1] = malloc(2 * sizeof(char*));
	cmd_list[1][0] = strdup("/bin/ls");
	cmd_list[1][1] = NULL;

	// cmd_list[2] = malloc(2 * sizeof(char*));
	// cmd_list[2][0] = strdup("/usr/bin/wc");
	// cmd_list[2][1] = NULL;

	// cmd_list[3] = malloc(2 * sizeof(char*));
	// cmd_list[3][0] = strdup("/usr/bin/wc");
	// cmd_list[3][1] = NULL;
	return cmd_list;
}


int main() {
	// char ***cmd_list = {{"/bin/ls", NULL}, {"/usr/bin/grep", "docker", NULL}, {"/usr/bin/wc", NULL}, {"/usr/bin/wc", NULL}};
	char ***cmd_list = set_cmd_list();
	int status = exec_pipe(cmd_list, 1);
	printf("status: %d\n", status);
	return 0;
}

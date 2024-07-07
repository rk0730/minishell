// コンパイル
// ccw -lreadline main.c

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv, char **envp) {
	int i = 0;
	while (envp[i] != NULL) {
		printf("envp[%d]: %s\n", i, envp[i]);
        i++;
	}
	
	return 0;
}

#include <libc.h>

__attribute__((destructor))
static void destructor() {
	system("leaks -q a.out");
}


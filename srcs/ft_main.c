

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char *input;

	while (1) {
		// Readlineを使用してユーザー入力を取得
		input = readline("MINISHELL$ ");

		//exitコマンドが入力されたら終了
		if (strncmp(input, "exit", 4) == 0) {
			// printf("finish minishell\n");
			free(input);
			return 0;
		}

		// lslならエラーメッセージを表示
		if (strncmp(input, "lsl", 3) == 0) {
			fprintf(stderr, "lsl: command not found\n");
			free(input);
			continue;
		}

		// printf("You entered: %s\n", input);
		printf("execute %s\n", input);

		// ヒストリーに入力を追加
		add_history(input);

		// 入力のメモリを解放
		free(input);
	}

	return 0;
}

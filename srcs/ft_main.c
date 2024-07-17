/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:37:13 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/16 17:59:08 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cmd.h"

int main(int argc, char **argv, char **envp) {
	char *input;
	int	status;

	status = 0;//初期化
	// 消す
	if (argc == 0)
		printf("%s", argv[0]);

	t_env_pair *env_list;
	env_list = ft_gen_env_list(envp);
	while (1) {
		// Readlineを使用してユーザー入力を取得
		input = readline("MINISHELL$ ");

		if (input == NULL)
		{
			printf("exit\n");
			return (WEXITSTATUS(status));
		}

		if (ft_strlen(input) == 0) {
			free(input);
			continue;
		}

		//exitコマンドが入力されたら終了
		if (strncmp(input, "exit", 4) == 0) {
			free(input);
			return (WEXITSTATUS(status));
		}

		// printf("execute %s\n", input);

		pid_t pid;
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(1);
		} else if (pid == 0) {
			// 子プロセス
			ft_exec_cmd(input, env_list);
		} else {
			// 親プロセス
			// 子プロセスの終了を待つ
			wait(&status);
		}


		// ヒストリーに入力を追加
		add_history(input);

		// 入力のメモリを解放
		free(input);
	}

	return (WEXITSTATUS(status));
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q minishell");
// }

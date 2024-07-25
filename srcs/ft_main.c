/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:37:13 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/25 20:45:28 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cmd.h"

int main(int argc, char **argv, char **envp) {
	char		*input;
	int			status;
	t_env_pair	*env_list;
	t_env_info	env_info;

	status = 0;//初期化
	// 消す
	if (argc == 0)
		printf("%s", argv[0]);

	env_list = ft_gen_env_list(envp);
	env_info.env_list = env_list;
	env_info.last_status = 0;
	while (1) {
		// Readlineを使用してユーザー入力を取得
		input = readline("MINISHELL$ ");

		if (input == NULL)
		{
			printf("exit\n");
			return (env_info.last_status);
		}

		if (ft_strlen(input) == 0) {
			free(input);
			continue;
		}

		//exitコマンドが入力されたら終了
		if (strncmp(input, "exit", 4) == 0) {
			free(input);
			return (env_info.last_status);
		}

		// printf("execute %s\n", input);

		// pid_t pid;
		// pid = fork();
		// if (pid == -1) {
		// 	perror("fork");
		// 	exit(1);
		// } else if (pid == 0) {
		// 	// 子プロセス
		// 	ft_exec_cmd(input, env_info);
		// } else {
		// 	// 親プロセス
		// 	// 子プロセスの終了を待つ
		// 	wait(&status);
		// 	env_info.last_status = WEXITSTATUS(status);
		// }
		env_info.last_status = ft_exec_cmdline(input, env_info);
		// printf("last_status: %d\n", env_info.last_status);


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

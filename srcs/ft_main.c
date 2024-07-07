/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:37:13 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/07 18:48:14 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "env.h"
#include "cmd.h"

int main(int argc, char **argv, char **envp) {
	char *input;

	// 消す
	if (argc == 0)
		printf("%s", argv[0]);

	// 環境変数を表示
	// t_env_pair **env_list = ft_gen_env_list(envp);
	t_env_pair **env_list;
	env_list = ft_gen_env_list(envp);
	
	
	// t_env_pair *tmp = *env_list;
	// while (tmp) {
	// 	printf("%s==%s\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }
	
	printf("%p %p %s====%s\n", env_list, (*env_list)->key, (*env_list)->key, (*env_list)->value);
	printf("--------------------------\n");
	printf("%p %p %s====%s\n", env_list, (*env_list)->key, (*env_list)->key, (*env_list)->value);
	printf("%p %p %s====%s\n", env_list, (*env_list)->key, (*env_list)->key, (*env_list)->value);
	printf("--------------------------\n");
	printf("%p %p %s====%s\n", env_list, (*env_list)->key, (*env_list)->key, (*env_list)->value);
	char **path_array = ft_gen_path_array(env_list);
	int i = 0;
	while (path_array[i])
	{
		printf("%s\n", path_array[i]);
		i++;
	}
	
	while (1) {
		// Readlineを使用してユーザー入力を取得
		input = readline("MINISHELL$ ");

		if (input == NULL)
		{
			printf("exit\n");
			return (0);
		}

		if (ft_strlen(input) == 0) {
			free(input);
			continue;
		}

		//exitコマンドが入力されたら終了
		if (strncmp(input, "exit", 4) == 0) {
			free(input);
			return 0;
		}

		// printf("execute %s\n", input);

		pid_t pid;
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(1);
		} else if (pid == 0) {
			// 子プロセス
			ft_exec_cmd(input);
		} else {
			// 親プロセス
			// 子プロセスの終了を待つ
			wait(NULL);
		}


		// ヒストリーに入力を追加
		add_history(input);

		// 入力のメモリを解放
		free(input);
	}

	return 0;
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q minishell");
// }

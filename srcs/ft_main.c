/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:37:13 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 19:19:20 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cmd.h"

static void	ft_sigint(int signum)
{
	(void)signum;
	ft_status_code(1, 130);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}



int main(int argc, char **argv, char **envp) {
	int			status;
	t_env_pair	*env_list;
	t_env_info	*env_info_p;

	status = 0;//初期化
	// 消す
	if (argc == 0)
		printf("%s", argv[0]);

	env_list = ft_gen_env_list(envp);
	env_info_p = (t_env_info *)malloc(sizeof(t_env_info));
	env_info_p->env_list = env_list;
	ft_status_code(1, 0);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1) {
		// Readlineを使用してユーザー入力を取得
		env_info_p->input = readline("MINISHELL$ ");

		if (env_info_p->input == NULL)
		{
			printf("exit\n");
			return (ft_status_code(0, 0));
		}

		if (ft_strlen(env_info_p->input) == 0) {
			free(env_info_p->input);
			continue;
		}

		//exitコマンドが入力されたら終了
		if (strncmp(env_info_p->input, "exit", 4) == 0) {
			free(env_info_p->input);
			return (ft_status_code(0, 0));
		}

		// printf("execute %s\n", env_info_p->input);

		// pid_t pid;
		// pid = fork();
		// if (pid == -1) {
		// 	perror("fork");
		// 	exit(1);
		// } else if (pid == 0) {
		// 	// 子プロセス
		// 	ft_exec_cmd(env_info_p->input, env_info_p);
		// } else {
		// 	// 親プロセス
		// 	// 子プロセスの終了を待つ
		// 	wait(&status);
		// 	env_info_p.last_status = WEXITSTATUS(status);
		// }
		ft_status_code(1, ft_exec_cmdline(env_info_p));
		// printf("last_status: %d\n", env_info_p->last_status);
		// printf("last input: %s\n", env_info_p->input);


		// ヒストリーに入力を追加
		add_history(env_info_p->input);

		// 入力のメモリを解放
		free(env_info_p->input);
	}

	return (WEXITSTATUS(status));
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q minishell");
// }

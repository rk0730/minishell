/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:37:13 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/01 11:35:28 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cmd.h"

volatile sig_atomic_t g_signum = 0;

static void	ft_sigint(int sig)
{
	(void)sig;
	ft_status_code(1, 130);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}



int main(int argc, char **argv, char **envp) {
	t_env_pair	*env_list;
	t_env_info	*env_info_p;
	int			input_pipe[2];

	// 消す
	if (argc == 0)
		printf("%s", argv[0]);

	env_list = ft_gen_env_list(envp);
	env_info_p = (t_env_info *)malloc(sizeof(t_env_info));
	env_info_p->env_list = env_list;
	ft_status_code(1, 0);
	while (1) {
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		// Readlineを使用してユーザー入力を取得
		env_info_p->input = readline("MINISHELL$ ");
		pipe(input_pipe);
		ft_printf_fd(input_pipe[1], "%s", env_info_p->input);
		close(input_pipe[1]);
		env_info_p->input_fd = input_pipe[0];

		if (env_info_p->input == NULL)
		{
			printf("exit\n");
			return (ft_status_code(0, 0));
		}

		if (ft_strlen(env_info_p->input) == 0)
		{
			free(env_info_p->input);
			continue ;
		}

		//exitコマンドが入力されたら終了
		if (strncmp(env_info_p->input, "exit", 4) == 0) {
			free(env_info_p->input);
			return (ft_status_code(0, 0));
		}

		ft_status_code(1, ft_exec_cmdline(env_info_p));
		// printf("last_status: %d\n", env_info_p->last_status);
		// printf("last input: %s\n", env_info_p->input);


		// ヒストリーに入力を追加
		add_history(env_info_p->input);

		g_signum = 0;

		// 入力のメモリを解放
		free(env_info_p->input);
	}

	return (ft_status_code(0, 0));
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q minishell");
// }

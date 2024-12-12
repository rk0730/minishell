/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:37:13 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/12 15:42:54 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "cmd.h"

volatile sig_atomic_t g_signum = 0;

static void	ft_sigint(int sig)
{
	(void)sig;
	ft_status_code(1, 130);
	ft_printf_fd(STDIN_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	_ft_is_all_space(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}


int	main(int argc, char **argv, char **envp)
{
	t_env_pair	*env_list;
	t_env_info	*env_info_p;

	RKITAO("print RKITAO\n");
	YYAMASAK("print YYAMASAK\n");
	(void)argc;
	(void)argv;
	env_list = ft_gen_env_list(envp);
	env_info_p = (t_env_info *)malloc(sizeof(t_env_info));
	env_info_p->env_list = env_list;
	ft_status_code(1, 0);
	ft_internal_pwd(1);
	while (1)
	{
		signal(SIGINT, ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		// Readlineを使用してユーザー入力を取得
		env_info_p->input = readline("MINISHELL$ ");
		// ctrl+dが押されるとNULLが返ってくるので終了
		if (env_info_p->input == NULL)
		{
			ft_free_env_list(env_list);
			free(env_info_p);
			ft_printf_fd(STDOUT_FILENO, "exit\n");
			exit(ft_status_code(0, 0));
		}
		// 空文字、もしくは全て空白文字の場合は何もせず次のループへ
		if (ft_strlen(env_info_p->input) == 0 || _ft_is_all_space(env_info_p->input))
		{
			free(env_info_p->input);
			continue ;
		}
		// コマンドを実行
		ft_status_code(1, ft_exec_cmdline(env_info_p));
		// ヒストリーに入力を追加
		add_history(env_info_p->input);
		g_signum = 0;
		free(env_info_p->input);
	}
	return (0);
}

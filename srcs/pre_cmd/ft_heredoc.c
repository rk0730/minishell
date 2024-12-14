/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/13 15:34:37 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static void	_ft_sigint_heredoc(int sig)
{
	g_signum = sig;
	ft_close(_ft_heredoc_write_fd(0, 0), 32);
	// デフォルトの SIGINT 動作させる
	signal(SIGINT, SIG_DFL);
	kill(getpid(), SIGINT);
}

// 引数fdより小さいファイルディスクリプタを全て閉じる
static void	_ft_close_all_fd(int fd)
{
	int	i;

	i = 3;
	while (i < fd)
	{
		ft_close(i, i);
		i++;
	}
}

static void	_ft_change_g_signum(int sig)
{
	g_signum = sig;
}

// heredocでの入力が入ったfdを返す 一回もheredocがなければ-1 エラーがあれば-2を返す fork使わないものに書き直し
// utils[0] = i (tokensのindex)
// utils[1] = result (前回のヒアドクの結果)
// utils[2] = is_quote ()
int	_ft_heredoc(char **tokens, t_env_info *env_info_p)
{
	int		pipe_fd[2];
	char	*limiter;
	int		utils[3];
	pid_t	pid;

	utils[0] = 0;
	utils[1] = -1;
	while (tokens[utils[0]])
	{
		if (ft_strncmp(tokens[utils[0]], "<<", 3) == 0)
		{
			// 前回のheredocがあれば不要なので閉じる
			if (utils[1] != -1)
				ft_close(utils[1], 34);
			//最後に<<がある場合、あとでエラー文は出すのでここでは出さない
			if (tokens[utils[0] + 1] == NULL)
				return (-2);
			pipe(pipe_fd);
			pid = fork();
			if (pid == -1)
				return (-1);
			if (pid == 0)
			{
				// 書き込みのpipe_fd[1]を閉じてデフォルトのSIGINT動作をする
				signal(SIGINT, _ft_sigint_heredoc);
				signal(SIGQUIT, SIG_IGN);
				ft_close(pipe_fd[0], 35);
				_ft_close_all_fd(pipe_fd[1]);
				limiter = _ft_limit_tokenize(tokens[utils[0] + 1], &utils[2]);
				if (limiter == NULL)
				{
					ft_printf_fd(STDERR_FILENO,
						"syntax error near unexpected token `newline'\n");
					exit(-2);
				}
				// ヒアドクが１つ実行してresultに格納
				_ft_one_heredoc(env_info_p, pipe_fd, limiter, utils[2]);
				free(limiter);
				exit(EXIT_SUCCESS);
			}
			else
			{
				signal(SIGINT, _ft_change_g_signum); // g_signumをSIGINTに変えるだけ
				signal(SIGQUIT, SIG_IGN);
				ft_close(pipe_fd[1], 36);
				waitpid(pid, &utils[1], 0);
				utils[1] = pipe_fd[0];
				if (g_signum == SIGINT)
				{
					ft_printf_fd(STDOUT_FILENO, "\n");
					ft_close(utils[1], 37);
					return (utils[1]);
				}
				if (WEXITSTATUS(utils[1]) == -2)
				{
					ft_close(pipe_fd[0], 37);
					return (-2);
				}
			}
		}
		utils[0]++;
	}
	return (utils[1]);
}

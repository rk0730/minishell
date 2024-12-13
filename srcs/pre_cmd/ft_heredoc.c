/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/13 11:35:22 by kitaoryoma       ###   ########.fr       */
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
int	_ft_heredoc(char **tokens, t_env_info *env_info_p)
{
	int		pipe_fd[2];
	int		i;
	char	*limiter;
	int		is_quote;
	int		result;
	pid_t	pid;

	i = 0;
	result = -1;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			// 前回のheredocがあれば不要なので閉じる
			if (result != -1)
				ft_close(result, 34);
			if (tokens[i + 1] == NULL)//最後に<<がある場合、あとでエラー文は出すのでここでは出さない
				return (-2);
			pipe(pipe_fd);
			pid = fork();
			if (pid == -1)
				return (-1);
			if (pid == 0)
			{
				signal(SIGINT, _ft_sigint_heredoc);// 書き込みのpipe_fd[1]を閉じてデフォルトのSIGINT動作をする
				signal(SIGQUIT, SIG_IGN);
				ft_close(pipe_fd[0], 35);
				_ft_close_all_fd(pipe_fd[1]);
				limiter = _ft_limit_tokenize(tokens[i + 1], &is_quote);
				if (limiter == NULL)
				{
					ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
					exit(-2);
				}
				// ヒアドクが１つ実行してresultに格納
				_ft_one_heredoc(env_info_p, pipe_fd, limiter, is_quote);
				exit(EXIT_SUCCESS);
			}
			else
			{
				signal(SIGINT, _ft_change_g_signum);//g_signumをSIGINTに変えるだけ
				signal(SIGQUIT, SIG_IGN);
				ft_close(pipe_fd[1], 36);
				waitpid(pid, &result, 0);
				result = pipe_fd[0];
				if (g_signum == SIGINT)
				{
					ft_printf_fd(STDOUT_FILENO, "\n");
					ft_close(result, 37);
					return (result);
				}
				if (WEXITSTATUS(result) == -2)
				{
					ft_close(pipe_fd[0], 37);
					return (-2);
				}
			}
		}
		i++;
	}
	return (result);
}

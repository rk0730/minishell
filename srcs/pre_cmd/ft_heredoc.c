/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/12 15:43:38 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// クォーテーションエラーがあった際はNULLを返すように作ったが、最初にクォーテーションはチェックしているため、ここでそのエラーが出ることはなさそう
// limiterを求める関数、"や'で囲まれているものはそのまま返す、 is_quoteはheredoc中に打ち込まれるものを展開する際の場合分けのflagになる
static char	*_ft_limit_tokenize(char *str, int *is_quote)
{
	char	*result;
	char	*tmp;
	char	*before;
	int		i;
	int		end;

	result = ft_strdup("");
	i = 0;
	*is_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			end = i + 1;
			while (str[end] != '\0' && str[end] != str[i])
				end++;
			//　クォーテーションエラーはおそらく起き得ないので削除
			// if (str[end] == '\0')
			// {
			// 	free(result);
			// 	return (NULL);
			// }
			tmp = ft_substr(str, i + 1, end - i - 1);
			end++;
		}
		else
		{
			end = i;
			while (str[end] != '\0' && str[end] != '\"' && str[end] != '\'')
				end++;
			tmp = ft_substr(str, i, end - i);
		}
		before = result;
		result = ft_strjoin(before, tmp);
		free(before);
		free(tmp);
		i = end;
	}
	// limiterにクォーテーションがあるか確認
	if (ft_strchr(str, '\'') != NULL || ft_strchr(str, '\"') != NULL)
		*is_quote = 1;
	return (result);
}

// heredocで書き込み中のfdを入れる　SIGINTが来た時にcloseできるように保持しておく
static int _ft_heredoc_write_fd(int flag, int fd)
{
	static int heredoc_write_fd;

	if (flag)
		heredoc_write_fd = fd;
	return (heredoc_write_fd);
}

static void	_ft_sigint_heredoc(int sig)
{
	g_signum = sig;
	ft_close(_ft_heredoc_write_fd(0, 0), 32);
	// デフォルトの SIGINT 動作させる
	signal(SIGINT, SIG_DFL);
	kill(getpid(), SIGINT);
}

static int	_ft_one_heredoc(t_env_info *env_info_p, int pipe_fd[2], char *limiter, int is_quote)
{
	char	*line;
	// char	*tmp;

	while (1)
	{
		_ft_heredoc_write_fd(1, pipe_fd[1]);
		line = readline("heredoc > ");
		if (line == NULL)
		{
			//lineがNULLということはctrl+dが押されたということ
			ft_printf_fd(STDERR_FILENO, "warning: here-document delimited by end-of-file (wanted `");
			write(STDERR_FILENO, limiter, ft_strlen(limiter));
			ft_printf_fd(STDERR_FILENO, "')\n");
			break ;
		}
		// 読み取った行とlimiterが一致したらループを抜ける
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		// 読み取った行と改行をfdに書き込む
		if (!is_quote)
			line = _ft_expand_env(line, *env_info_p, 1);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	ft_close(pipe_fd[1], 33);
	free(limiter);
	return (0);
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

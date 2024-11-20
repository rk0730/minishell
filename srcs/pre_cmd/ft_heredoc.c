/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/18 09:36:15 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static void	_ft_sigint_heredoc(int sig)
{
	g_signum = sig;
	printf("\n");
	ft_close(STDIN_FILENO, 31);
}

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

static void	_ft_one_heredoc_h(t_env_info *env_info_p, char *line)
{
	char	*tmp;

	// 初めての入力の場合、改行を追加
	if (ft_strchr(env_info_p->input, '\n') == NULL)
	{
		tmp = env_info_p->input;
		env_info_p->input = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	// 読み取った行と改行を履歴に追加
	tmp = env_info_p->input;
	env_info_p->input = ft_strjoin(tmp, line);
	free(tmp);
	tmp = env_info_p->input;
	env_info_p->input = ft_strjoin(tmp, "\n");
	free(tmp);
}

static int	_ft_one_heredoc(t_env_info *env_info_p, int pipe_fd[2], char *limiter, int is_quote)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = get_next_line(env_info_p->input_fd);
		tmp = line;
		line = ft_strtrim(tmp, "\n");
		free(tmp);
		if (line == NULL)
			line = readline("heredoc > ");//最初に入力したinput_fdが切れたので標準入力から受け取る
		if (line == NULL)
		{
			if (g_signum == SIGINT)
			{
				ft_close(pipe_fd[1], 32);
				return (-2);
			}
			else
			{
				//lineがNULLなのにSIGINTではないということはctrl+dが押されたということ
				ft_printf_fd(STDERR_FILENO, "warning: here-document delimited by end-of-file (wanted `");
				write(STDERR_FILENO, limiter, ft_strlen(limiter));
				ft_printf_fd(STDERR_FILENO, "')\n");
				break ;
			}
		}
		_ft_one_heredoc_h(env_info_p, line);
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

// heredocでの入力が入ったfdを返す 一回もheredocがなければ-1 エラーがあれば-2を返す fork使わないものに書き直し
int	_ft_heredoc(char **tokens, t_env_info *env_info_p)
{
	int		pipe_fd[2];
	int		i;
	char	*limiter;
	int		is_quote;
	int		result;

	i = 0;
	result = -1;
	signal(SIGINT, _ft_sigint_heredoc);
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
			limiter = _ft_limit_tokenize(tokens[i + 1], &is_quote);
			if (limiter == NULL)
			{
				ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
				return (-2);
			}
			// ヒアドクが１つ実行してresultに格納
			if (_ft_one_heredoc(env_info_p, pipe_fd, limiter, is_quote) == -2)
				return (-2);
			result = pipe_fd[0];
		}
		i++;
	}
	return (result);
}

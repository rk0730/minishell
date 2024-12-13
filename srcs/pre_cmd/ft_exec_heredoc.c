/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:24:50 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 11:32:44 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

// heredocで書き込み中のfdを入れる　SIGINTが来た時にcloseできるように保持しておく
int _ft_heredoc_write_fd(int flag, int fd)
{
	static int heredoc_write_fd;

	if (flag)
		heredoc_write_fd = fd;
	return (heredoc_write_fd);
}

int	_ft_one_heredoc(t_env_info *env_info_p, int pipe_fd[2], char *limiter, int is_quote)
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

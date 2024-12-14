/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:24:50 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 17:54:01 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

int	_ft_heredoc_write_fd(int flag, int fd)
{
	static int	heredoc_write_fd;

	if (flag)
		heredoc_write_fd = fd;
	return (heredoc_write_fd);
}

int	_ft_one_heredoc(t_env_info *env_info_p, int pipe_fd[2], char *limiter,
		int is_quote)
{
	char	*line;

	while (1)
	{
		_ft_heredoc_write_fd(1, pipe_fd[1]);
		line = readline("heredoc > ");
		if (line == NULL)
		{
			ft_printf_fd(STDERR_FILENO,
				"warning: here-document delimited by end-of-file (wanted `");
			ft_putendl_fd(limiter, STDERR_FILENO);
			break ;
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (!is_quote)
			line = _ft_expand_env(line, *env_info_p, 1);
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	ft_close(pipe_fd[1], 33);
	return (0);
}

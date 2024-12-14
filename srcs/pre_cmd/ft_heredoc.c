/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:35:53 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 16:59:08 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static int	_ft_help3(int *utils)
{
	if (g_signum == SIGINT)
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		ft_close(utils[1], 37);
		return (1);
	}
	return (0);
}

static void	_ft_help2(pid_t *pid, int *pipe_fd, int *utils)
{
	signal(SIGINT, _ft_change_g_signum);
	signal(SIGQUIT, SIG_IGN);
	ft_close(pipe_fd[1], 36);
	waitpid(*pid, NULL, 0);
	utils[1] = pipe_fd[0];
}

static void	_ft_help1(int *pipe_fd, t_env_info *env_info_p,
		int *utils, char **tokens)
{
	char	*limiter;

	signal(SIGINT, _ft_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	ft_close(pipe_fd[0], 35);
	_ft_close_all_fd(pipe_fd[1]);
	limiter = _ft_limit_tokenize(tokens[utils[0] + 1], &utils[2]);
	_ft_one_heredoc(env_info_p, pipe_fd, limiter, utils[2]);
	free(limiter);
	exit(EXIT_SUCCESS);
}

int	_ft_heredoc(char **tokens, t_env_info *env_info_p)
{
	int		pipe_fd[2];
	int		utils[3];
	pid_t	pid;

	utils[0] = 0;
	utils[1] = -1;
	while (tokens[utils[0]])
	{
		if (ft_strncmp(tokens[utils[0]], "<<", 3) == 0)
		{
			if (utils[1] != -1)
				ft_close(utils[1], 34);
			if (tokens[utils[0] + 1] == NULL)
				return (-2);
			pipe(pipe_fd);
			pid = fork();
			if (pid == 0)
				_ft_help1(pipe_fd, env_info_p, utils, tokens);
			_ft_help2(&pid, pipe_fd, utils);
			if (_ft_help3(utils) == 1)
				return (utils[1]);
		}
		utils[0]++;
	}
	return (utils[1]);
}

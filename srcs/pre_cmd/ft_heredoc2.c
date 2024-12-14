/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:41:19 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/14 17:51:22 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

void	_ft_sigint_heredoc(int sig)
{
	g_signum = sig;
	ft_close(_ft_heredoc_write_fd(0, 0), 32);
	signal(SIGINT, SIG_DFL);
	kill(getpid(), SIGINT);
}

void	_ft_close_all_fd(int fd)
{
	int	i;

	i = 3;
	while (i < fd)
	{
		ft_close(i, i);
		i++;
	}
}

void	_ft_change_g_signum(int sig)
{
	g_signum = sig;
}

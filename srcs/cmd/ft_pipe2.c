/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:15:07 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/14 15:44:07 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	_ft_wait_pipe(pid_t pid)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	_ft_print_newline(int sig)
{
	(void)sig;
	ft_printf_fd(STDOUT_FILENO, "\n");
}

void	_ft_close_fd_inout(t_cmd_info *cmd_list, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{
		ft_close(cmd_list[i].fd_in, 42);
		ft_close(cmd_list[i].fd_out, 43);
		i++;
	}
}

int	_ft_exec_one_cmd(t_cmd_info *cmd_list, t_env_info *env_info_p)
{
	int		status;

	status = ft_exec_cmd(cmd_list[0], env_info_p, -1, -1);
	YYAMASAK("status=%d\n", status);
	if (g_signum == SIGINT)
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		return (SIGINT_ERROR);
	}
	else if (g_signum == SIGQUIT)
	{
		ft_printf_fd(STDOUT_FILENO, "Quit (core dumped)\n");
		return (SIGQUIT_ERROR);
	}
	else
		return (status);
}

void	_ft_wait_signal(int status)
{
	if (g_signum == SIGINT)
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		exit(SIGINT_ERROR);
	}
	else if (g_signum == SIGQUIT)
	{
		ft_printf_fd(STDOUT_FILENO, "Quit (core dumped)\n");
		exit(SIGQUIT_ERROR);
	}
	else
	{
		exit(status);
	}
}

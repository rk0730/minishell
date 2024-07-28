/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 13:14:50 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"


// i個目のコマンドを実行し、終了ステータスを返す
static int	ft_recursive(t_cmd_info *cmd_list, t_env_info env_info, int i, int out_fd)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	// 最初のコマンド
	if (i == 0)
		return (ft_exec_cmd(cmd_list[i], env_info, -1, out_fd));
	//途中、最後のコマンド
	if (pipe(pipe_fd) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipe: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_printf_fd(STDERR_FILENO, "fork: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)//子プロセス
	{
		status = ft_recursive(cmd_list, env_info, i - 1, pipe_fd[1]);
		exit(status);
	}
	else
	{
		//親プロセス
		//コマンドを実行する
		close(pipe_fd[1]);
		status = ft_exec_cmd(cmd_list[i], env_info, pipe_fd[0], out_fd);
		// wait(NULL);
		waitpid(pid, NULL, 0);
		return (status);
	}
	return (0);
}

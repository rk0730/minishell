/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:24:47 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/12 18:31:35 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


// #include <unistd.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <errno.h>

// fdが開いているかどうかを判定する
// static int	is_fd_open(int fd) {
// 	return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
// }

// pipeに入出力するのか、ファイルに入出力するのかを判断する
void	ft_choose_fd(t_cmd_info cmd_info, int read_pipe, int write_pipe, t_bool need_input)
{
	if (cmd_info.fd_in != -1)
	{
		if (need_input)
			dup2(cmd_info.fd_in, STDIN_FILENO);
	}
	else if (read_pipe != -1)
	{
		if (need_input)
			dup2(read_pipe, STDIN_FILENO);
	}
	if (cmd_info.fd_out != -1)
	{
		dup2(cmd_info.fd_out, STDOUT_FILENO);
	}
	else if (write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
	}
	ft_close(cmd_info.fd_in, 4);
	ft_close(cmd_info.fd_out, 5);
	ft_close(read_pipe, 6);
	ft_close(write_pipe, 7);
}

// ビルトインを呼び出し、終了ステータスを返す　見つからなかったら-1を返す
static int	ft_call_builtin(t_cmd_info cmd_info, t_env_info *env_info_p, int rw_pipe[2], int std_in_out[2])
{
	if (ft_strncmp(cmd_info.cmd_argv[0], "echo", 5) == 0)
		return (ft_echo(cmd_info, *env_info_p));
	if (ft_strncmp(cmd_info.cmd_argv[0], "cd", 3) == 0)
		return (ft_cd(cmd_info, *env_info_p));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "pwd", 4) == 0)
		return (ft_pwd(cmd_info, *env_info_p));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "export", 7) == 0)
		return (ft_export(cmd_info, *env_info_p));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "unset", 6) == 0)
		return (ft_unset(cmd_info, env_info_p));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "env", 4) == 0)
		return (ft_env(cmd_info, *env_info_p));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "exit", 5) == 0)
	{
		ft_close(std_in_out[0], 8);
		ft_close(std_in_out[1], 9);
		return (ft_exit(cmd_info, *env_info_p, rw_pipe[0], rw_pipe[1]));
	}
	else
		return (-1);
}

// ビルトインコマンドかどうか確認し、前処理を行う
int	ft_builtin(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe)
{
	int rw_pipe[2];
	int std_in_out[2];
	int result;

	if (ft_strncmp(cmd_info.cmd_argv[0], "echo", 5 == 0)
		|| ft_strncmp(cmd_info.cmd_argv[0], "cd", 3) == 0
		|| ft_strncmp(cmd_info.cmd_argv[0], "pwd", 4) == 0
		|| ft_strncmp(cmd_info.cmd_argv[0], "export", 7) == 0
		|| ft_strncmp(cmd_info.cmd_argv[0], "unset", 6) == 0
		|| ft_strncmp(cmd_info.cmd_argv[0], "env", 4) == 0
		|| ft_strncmp(cmd_info.cmd_argv[0], "exit", 5) == 0)
	{
		ft_choose_fd(cmd_info, read_pipe, write_pipe, FALSE);
		rw_pipe[0] = read_pipe;
		rw_pipe[1] = write_pipe;
		std_in_out[0] = dup(STDIN_FILENO);
		std_in_out[1] = dup(STDOUT_FILENO);
		result = ft_call_builtin(cmd_info, env_info_p, rw_pipe, std_in_out);
		dup2(std_in_out[0], STDIN_FILENO);
		dup2(std_in_out[1], STDOUT_FILENO);
		ft_close(std_in_out[0], 1);
		ft_close(std_in_out[1], 2);
		return (result);
	}
	return (-1);
}

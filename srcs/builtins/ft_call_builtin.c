/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_call_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:24:47 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/29 00:31:03 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "builtins.h"

// pipeに入出力するのか、ファイルに入出力するのかを判断する
void	ft_choose_fd(t_cmd_info cmd_info, int read_pipe, int write_pipe)
{
	if (cmd_info.fd_in != -1)
	{
		close(read_pipe);
		dup2(cmd_info.fd_in, STDIN_FILENO);
		close(cmd_info.fd_in);
	} else if (read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	if (cmd_info.fd_out != -1)
	{
		close(write_pipe);
		dup2(cmd_info.fd_out, STDOUT_FILENO);
		close(cmd_info.fd_out);
	} else if (write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
}

// ビルトインを呼び出し、終了ステータスを返す　見つからなかったら-1を返す
int	ft_call_builtin(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe)
{
	if (ft_strncmp(cmd_info.cmd_argv[0], "echo", 5) == 0)
		return (ft_echo(cmd_info, *env_info_p, read_pipe, write_pipe));
	if (ft_strncmp(cmd_info.cmd_argv[0], "cd", 3) == 0)
		return (ft_cd(cmd_info, *env_info_p, read_pipe, write_pipe));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "pwd", 4) == 0)
		return (ft_pwd(cmd_info, *env_info_p, read_pipe, write_pipe));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "export", 7) == 0)
		return (ft_export(cmd_info, *env_info_p, read_pipe, write_pipe));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "unset", 6) == 0)
		return (ft_unset(cmd_info, env_info_p, read_pipe, write_pipe));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "env", 4) == 0)
		return (ft_env(cmd_info, *env_info_p, read_pipe, write_pipe));
	else if (ft_strncmp(cmd_info.cmd_argv[0], "exit", 5) == 0)
		return (ft_exit(cmd_info, *env_info_p, read_pipe, write_pipe));
	else
		return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/25 21:17:11 by rkitao           ###   ########.fr       */
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

// コマンドを実行し、終了ステータスを返す
int	ft_exec_cmdline(char *input, t_env_info env_info)
{
	char		**cmds;
	t_cmd_info	*cmd_list;
	int			i;
	int			std_in;
	int			std_out;
	int			status;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	cmds = ft_gen_cmds(input);
	if (!cmds)
		return (SYNTAX_ERROR);
	cmd_list = ft_cmd_info_list(cmds, env_info);
	if (!cmd_list)
	{
		ft_free_array(cmds);
		return (SYNTAX_ERROR);
	}
	i = ft_array_len(cmds) - 1;
	status = ft_recursive(cmd_list, env_info, i, -1);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
	ft_free_array(cmds);
	free(cmd_list);
	return (status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 14:16:42 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void ft_recursive(t_cmd_info *cmd_list, t_env_info env_info, int index, int pipe_fd[4]) {
	pid_t pid;
	// pid_t pid2;

	if (index == 0) {
		close(pipe_fd[0]);
		pid = fork();
		if (pid == 0) {
			// dup2(pipe_fd[1], STDOUT_FILENO);
			// close(pipe_fd[1]);
			// execve(cmd_list[index][0], cmd_list[index], NULL);
			ft_exec_cmd(cmd_list[index], env_info, -1, pipe_fd[1]);
			exit(EXIT_SUCCESS);
		} else {
			close(pipe_fd[1]);
			waitpid(pid, NULL, 0);
		}
	} else {
		pipe(pipe_fd + 2);
		pid = fork();
		if (pid == 0) {
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			pipe_fd[0] = pipe_fd[2];
			pipe_fd[1] = pipe_fd[3];
			ft_recursive(cmd_list, env_info, index - 1, pipe_fd);
			exit(EXIT_SUCCESS);
		} else {
			close(pipe_fd[0]);
			close(pipe_fd[3]);
			// pid2 = fork();
			// if (pid2 == 0) {
			// 	// dup2(pipe_fd[2], STDIN_FILENO);
			// 	// close(pipe_fd[2]);
			// 	// dup2(pipe_fd[1], STDOUT_FILENO);
			// 	// close(pipe_fd[1]);
			// 	ft_exec_cmd(cmd_list[index], env_info, pipe_fd[2], pipe_fd[1]);
			// 	exit(EXIT_SUCCESS);
			// } else {
			// 	close(pipe_fd[2]);
			// 	close(pipe_fd[1]);
			// 	waitpid(pid2, NULL, 0);
			// }
			ft_exec_cmd(cmd_list[index], env_info, pipe_fd[2], pipe_fd[1]);
			waitpid(pid, NULL, 0);
		}
	}
}	

int	ft_exec_pipe(t_cmd_info *cmd_list, t_env_info env_info, int last_index)
{
	int pipe_fd[4];
	pid_t pid;
	// pid_t pid2;
	int status;

	if (last_index == 0) {
		return (ft_exec_cmd(cmd_list[0], env_info, -1, -1));
	}
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0) {
		//再帰
		ft_recursive(cmd_list, env_info, last_index - 1, pipe_fd);
		exit(0);
	} else {
		//親プロセス
		//最後のコマンドを実行する
		close(pipe_fd[1]);
		// pid2 = fork();
		// if (pid2 == 0) {
		// 	ft_exec_cmd(cmd_list[last_index], env_info, pipe_fd[0], -1);
		// 	exit(0);
		// } else {
		// 	close(pipe_fd[0]);
		// 	waitpid(pid2, &status, 0);
		// }
		status = ft_exec_cmd(cmd_list[last_index], env_info, pipe_fd[0], -1);
		waitpid(pid, NULL, 0);
		return (status);
	}
}


// i個目のコマンドを実行し、終了ステータスを返す
// int	ft_recursive(t_cmd_info *cmd_list, t_env_info env_info, int i, int out_fd)
// {
// 	int		pipe_fd[2];
// 	pid_t	pid;
// 	int		status;

// 	// 最初のコマンド
// 	if (i == 0)
// 		return (ft_exec_cmd(cmd_list[i], env_info, -1, out_fd));
// 	//途中、最後のコマンド
// 	if (pipe(pipe_fd) == -1)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "pipe: %s\n", strerror(errno));
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "fork: %s\n", strerror(errno));
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)//子プロセス
// 	{
// 		status = ft_recursive(cmd_list, env_info, i - 1, pipe_fd[1]);
// 		exit(status);
// 	}
// 	else
// 	{
// 		//親プロセス
// 		//コマンドを実行する
// 		close(pipe_fd[1]);
// 		status = ft_exec_cmd(cmd_list[i], env_info, pipe_fd[0], out_fd);
// 		// wait(NULL);
// 		waitpid(pid, NULL, 0);
// 		return (status);
// 	}
// 	return (0);
// }

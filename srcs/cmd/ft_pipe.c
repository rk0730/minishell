/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/01 04:18:51 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	ft_recursive(t_cmd_info *cmd_list, t_env_info env_info, int index, int pipe_fd[4])
{
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

// パイプを使う　ここに入ったプロセスは全てexitされる
static void	ft_exec_pipe(t_cmd_info *cmd_list, t_env_info env_info, int last_index)
{
	int pipe_fd[4];
	pid_t pid;
	// pid_t pid2;
	int status;

	//子プロセスなのでシグナルは無視する
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0) {
		//再帰
		ft_recursive(cmd_list, env_info, last_index - 1, pipe_fd);
		exit(EXIT_SUCCESS);
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
		exit(status);
	}
}

// cmd_listにまとめた全コマンドを実行し、終了ステータスを返す（複数コマンドがあればft_exec_pipeにまわす）
int	ft_exec_cmd_list(t_cmd_info *cmd_list, t_env_info env_info, int last_index)
{
	pid_t pid;
	int status;

	if (last_index == 0) {
		status = ft_exec_cmd(cmd_list[0], env_info, -1, -1);
		if (status == SIGINT)
		{
			printf("\n");
			return (SIGINT_ERROR);
		}
		else if (status == SIGQUIT)
		{
			printf("Quit\n");
			return (SIGQUIT_ERROR);
		}
		else if (status == 1)
			return (status);
		return (WEXITSTATUS(status));
	}
	pid = fork();
	if (pid == 0) {
		ft_exec_pipe(cmd_list, env_info, last_index);
	} else {
		signal(SIGINT, ft_change_g_signum);
		signal(SIGQUIT, ft_change_g_signum);
		waitpid(pid, &status, 0);
		if (g_signum == SIGINT)
		{
			printf("\n");
			if (status != 0)
				return (SIGINT_ERROR);
			return (WEXITSTATUS(status));
		}
		else if (g_signum == SIGQUIT)
		{
			if (status != 0)
			{
				printf("Quit\n");
				return (SIGQUIT_ERROR);
			}
			return (WEXITSTATUS(status));
		}
		return (WEXITSTATUS(status));
	}
	ft_printf_fd(STDERR_FILENO, "error in ft_exec_cmd_list\n");
	return (-1);
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

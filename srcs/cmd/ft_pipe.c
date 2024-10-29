/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/10/29 10:36:04 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"


// 最初のコマンドを実行して終了
static void	ft_recursive_fin(t_cmd_info *cmd_list, t_env_info *env_info_p, int index, int pipe_fd[4])
{
	pid_t	pid;

	close(pipe_fd[0]);
	pid = fork();
	if (pid == 0)
	{
		ft_exec_cmd(cmd_list[index], env_info_p, -1, pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_recursive(t_cmd_info *cmd_list, t_env_info *env_info_p, int index, int pipe_fd[4])
{
	pid_t	pid;

	if (index == 0)
		ft_recursive_fin(cmd_list, env_info_p, index, pipe_fd);
	else
	{
		pipe(pipe_fd + 2);
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			pipe_fd[0] = pipe_fd[2];
			pipe_fd[1] = pipe_fd[3];
			ft_recursive(cmd_list, env_info_p, index - 1, pipe_fd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[3]);
			ft_exec_cmd(cmd_list[index], env_info_p, pipe_fd[2], pipe_fd[1]);
			waitpid(pid, NULL, 0);
		}
	}
}

// パイプを使う　ここに入ったプロセスは全てexitされる
static void	ft_exec_pipe(t_cmd_info *cmd_list, t_env_info *env_info_p, int last_index)
{
	int		pipe_fd[4];
	pid_t	pid;
	int		status;

	//子プロセスなのでシグナルは無視する
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		//再帰
		ft_recursive(cmd_list, env_info_p, last_index - 1, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		//親プロセス
		//最後のコマンドを実行する
		close(pipe_fd[1]);
		status = ft_exec_cmd(cmd_list[last_index], env_info_p, pipe_fd[0], -1);
		waitpid(pid, NULL, 0);
		exit(status);
	}
}

// コマンドが1つしかないのでそれを実行して終了ステータスを返す
static int	ft_exec_one_cmd(t_cmd_info *cmd_list, t_env_info *env_info_p)
{
	int		status;

	status = ft_exec_cmd(cmd_list[0], env_info_p, -1, -1);
	if (status % 128 == SIGINT)
	{
		printf("\n");
		return (SIGINT_ERROR);
	}
	else if (status % 128 == SIGQUIT)
	{
		printf("Quit\n");
		return (SIGQUIT_ERROR);
	}
	else
		return (status);
}

// ft_exec_pipeの終了を待つ部分
static int	ft_wait_pipe(pid_t pid)
{
	int		status;

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

// cmd_listにまとめた全コマンドを実行し、終了ステータスを返す（複数コマンドがあればft_exec_pipeにまわす）
int	ft_exec_cmd_list(t_cmd_info *cmd_list, t_env_info *env_info_p, int last_index)
{
	pid_t	pid;

	if (last_index == 0)
		return (ft_exec_one_cmd(cmd_list, env_info_p));
	pid = fork();
	if (pid == 0)
	{
		ft_exec_pipe(cmd_list, env_info_p, last_index);
	}
	else
		return (ft_wait_pipe(pid));
	ft_printf_fd(STDERR_FILENO, "error in ft_exec_cmd_list\n");
	return (-1);
}

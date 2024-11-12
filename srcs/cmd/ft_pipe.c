/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/11 23:01:26 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// cmd_info[0]からcmd_info[index-1]までのfd_in, fd_outを閉じる
static void	ft_close_fd_inout(t_cmd_info *cmd_list, int index)
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


// 最初のコマンドを実行して終了
static void	ft_recursive_fin(t_cmd_info *cmd_list, t_env_info *env_info_p, int index, int pipe_fd[4])
{
	pid_t	pid;

	ft_close(pipe_fd[0], 44);
	pid = fork();
	if (pid == 0)
	{
		//他のコマンドのfd_in, fd_outを閉じる
		ft_exec_cmd(cmd_list[index], env_info_p, -1, pipe_fd[1]);
		ft_close(env_info_p->std_in, 45);
		ft_close(env_info_p->std_out, 46);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_close(pipe_fd[1], 47);
		ft_close(cmd_list[index].fd_out, 48);
		ft_close(cmd_list[index].fd_in, 49);
		ft_close(env_info_p->std_in, 50);
		ft_close(env_info_p->std_out, 51);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_recursive(t_cmd_info *cmd_list, t_env_info *env_info_p, int index, int pipe_fd[4])
{
	pid_t	pid;

	if (index == 0){
		ft_recursive_fin(cmd_list, env_info_p, index, pipe_fd);
	}
	else
	{
		pipe(pipe_fd + 2);
		pid = fork();
		if (pid == 0)
		{
			ft_close(pipe_fd[0], 52);
			ft_close(pipe_fd[1], 53);
			pipe_fd[0] = pipe_fd[2];
			pipe_fd[1] = pipe_fd[3];
			// ここで実行しない最後のコマンドのfd_in, fd_outを閉じる
			ft_close(cmd_list[index].fd_in, 54);
			ft_close(cmd_list[index].fd_out, 55);
			ft_recursive(cmd_list, env_info_p, index - 1, pipe_fd);
			exit(EXIT_SUCCESS);
		}
		else
		{
			//他のコマンドのfd_in, fd_outを閉じる
			ft_close_fd_inout(cmd_list, index);
			ft_close(pipe_fd[0], 56);
			ft_close(pipe_fd[3], 57);
			ft_exec_cmd(cmd_list[index], env_info_p, pipe_fd[2], pipe_fd[1]);
			ft_close(env_info_p->std_in, 58);
			ft_close(env_info_p->std_out, 59);
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
		// ここで実行しない最後のコマンドのfd_in, fd_outを閉じる
		ft_close(cmd_list[last_index].fd_in, 60);
		ft_close(cmd_list[last_index].fd_out, 61);
		ft_recursive(cmd_list, env_info_p, last_index - 1, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		//親プロセス
		//最後のコマンドを実行する
		//他のコマンドのfd_in, fd_outを閉じる
		ft_close_fd_inout(cmd_list, last_index);
		ft_close(pipe_fd[1], 62);
		status = ft_exec_cmd(cmd_list[last_index], env_info_p, pipe_fd[0], -1);
		ft_close(env_info_p->std_in, 63);
		ft_close(env_info_p->std_out, 64);
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

	// printf("fd_in:%d, fd_out:%d in ft_exec_cmd_list\n", cmd_list[last_index].fd_in, cmd_list[last_index].fd_out);
	if (last_index == 0)
		return (ft_exec_one_cmd(cmd_list, env_info_p));
	pid = fork();
	if (pid == 0)
	{
		ft_exec_pipe(cmd_list, env_info_p, last_index);
	}
	else
	{
		ft_close_fd_inout(cmd_list, last_index+1);
		return (ft_wait_pipe(pid));
	}
	ft_printf_fd(STDERR_FILENO, "error in ft_exec_cmd_list\n");
	return (-1);
}

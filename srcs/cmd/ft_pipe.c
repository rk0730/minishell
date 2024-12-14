/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:40:42 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 15:21:20 by kitaoryoma       ###   ########.fr       */
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
static void	ft_recursive_fin(t_cmd_info *cmd_list,
		t_env_info *env_info_p, int index, int pipe_fd[4])
{
	pid_t	pid;

	ft_close(pipe_fd[0], 44);
	pid = fork();
	if (pid == 0)
	{
		//他のコマンドのfd_in, fd_outを閉じる
		RKITAO("process %d: exec first write fd: %d\n", getpid(), pipe_fd[1]);
		ft_exec_cmd(cmd_list[index], env_info_p, -1, pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_close(pipe_fd[1], 47);
		ft_close(cmd_list[index].fd_out, 48);
		ft_close(cmd_list[index].fd_in, 49);
		waitpid(pid, NULL, 0);
	}
}

static void	ft_recursive(t_cmd_info *cmd_list,
		t_env_info *env_info_p, int index, int pipe_fd[4])
{
	pid_t	pid;

	if (index == 0)
	{
		ft_recursive_fin(cmd_list, env_info_p, index, pipe_fd);
		return ;
	}
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
		RKITAO("process %d: exec %s\n", getpid(), cmd_list[index].cmd_argv[0]);
		ft_exec_cmd(cmd_list[index], env_info_p, pipe_fd[2], pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
}

void	_ft_print_newline(int sig)
{
	(void)sig;
	ft_printf_fd(STDOUT_FILENO, "\n");
}

// パイプを使う　ここに入ったプロセスは全てexitされる
static void	ft_exec_pipe(t_cmd_info *cmd_list,
		t_env_info *env_info_p, int last_index)
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
		RKITAO("process %d: exec last command\n", getpid());
		ft_close_fd_inout(cmd_list, last_index);
		ft_close(pipe_fd[1], 62);
		status = ft_exec_cmd(cmd_list[last_index], env_info_p, pipe_fd[0], -1);
		// 最後のコマンドの実行が終わったので、これらのプロセスはもうシグナルを受け付けない
		signal(SIGINT, _ft_print_newline);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, NULL, 0);
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
}

// コマンドが1つしかないのでそれを実行して終了ステータスを返す
// TODO change status ??
static int	ft_exec_one_cmd(t_cmd_info *cmd_list, t_env_info *env_info_p)
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

// ft_exec_pipeの終了を待つ部分
static int	ft_wait_pipe(pid_t pid)
{
	int		status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

// cmd_listにまとめた全コマンドを実行し、終了ステータスを返す（複数コマンドがあればft_exec_pipeにまわす）
int	ft_exec_cmd_list(t_cmd_info *cmd_list,
	t_env_info *env_info_p, int last_index)
{
	pid_t	pid;

	if (last_index == 0)
		return (ft_exec_one_cmd(cmd_list, env_info_p));
	RKITAO("process %d: wait for pipe\n", getpid());
	pid = fork();
	if (pid == 0)
	{
		// SIGPIPE: 読み取り側が閉じているのに書き込むとこのシグナルによってプロセスが落ちる
		// SIGPIPEで勝手に落ちられるとcloseすべきものをcloseし忘れるなど不都合なことがおきるので無視する
		signal(SIGPIPE, SIG_IGN);
		ft_exec_pipe(cmd_list, env_info_p, last_index);
	}
	else
	{
		ft_close_fd_inout(cmd_list, last_index + 1);
		return (ft_wait_pipe(pid));
	}
	ft_printf_fd(STDERR_FILENO, "error in ft_exec_cmd_list\n");
	return (-1);
}

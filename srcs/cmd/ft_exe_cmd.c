/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/08/02 17:24:26 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	ft_find_and_exec(t_cmd_info cmd_info, char **cmd_env, char **path_array)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_info.cmd_argv[0]);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			// if (cmd_info.fd_out != -1)
			// 	dup2(cmd_info.fd_out, STDOUT_FILENO);
			// if (cmd_info.fd_in != 1)
			// 	dup2(cmd_info.fd_in, STDIN_FILENO);
			if (execve(cmd_path, cmd_info.cmd_argv, cmd_env) == -1)
				exit(CMD_ERROR);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd_info.cmd_argv[0]);
	ft_free_array(cmd_info.cmd_argv);
	exit(CMD_NOT_FOUND);
}

static void	ft_exec_direct(t_cmd_info cmd_info, char **cmd_env)
{
	// if (cmd_info.fd_out != -1)
	// 	dup2(cmd_info.fd_out, STDOUT_FILENO);
	// if (cmd_info.fd_in != 1)
	// 	dup2(cmd_info.fd_in, STDIN_FILENO);
	if (execve(cmd_info.cmd_argv[0], cmd_info.cmd_argv, cmd_env) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0], strerror(errno));
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_info.cmd_argv);
}

// コマンドを実行する（execveならfork ビルトインならそのまま）終了ステータスを返す
int	ft_exec_cmd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	char	**path_array;
	char	**cmd_env;
	int		status;
	pid_t	pid;

	//表示
	// printf("cmd_argv: ");
	// ft_show_all(cmd_info.cmd_argv);
	// printf("fd_in: %d\n", cmd_info.fd_in);
	// printf("fd_out: %d\n", cmd_info.fd_out);
	// printf("read_pipe: %d\n", read_pipe);
	// printf("write_pipe: %d\n", write_pipe);
	if (cmd_info.fd_out == -2 || cmd_info.fd_in == -2)
	{
		close(read_pipe);
		close(write_pipe);
		return (EXIT_FAILURE);
	}
	if (ft_array_len(cmd_info.cmd_argv) == 0)
	{
		close(cmd_info.fd_in);
		close(cmd_info.fd_out);
		close(read_pipe);
		close(write_pipe);
		return (EXIT_SUCCESS);
	}
	//ビルトインの場合はforkせずにここで実行し、終了ステータスを返す
	status = ft_call_builtin(cmd_info, env_info, read_pipe, write_pipe);
	if (status != -1)
		return (status);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		// pipeに入出力するのか、ファイルに入出力するのかを判断する
		ft_choose_fd(cmd_info, read_pipe, write_pipe);
		//シグナルはデフォに戻す
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		path_array = ft_gen_path_array(env_info.env_list);
		cmd_env = ft_gen_cmd_env(env_info.env_list);
		if (ft_strchr(cmd_info.cmd_argv[0], '/') != NULL)
			ft_exec_direct(cmd_info, cmd_env);
		else
			ft_find_and_exec(cmd_info, cmd_env, path_array);
	}
	else
	{
		close(cmd_info.fd_out);
		close(cmd_info.fd_in);
		close(read_pipe);
		close(write_pipe);
		//親プロセスはシグナルを無視する
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		return (status);
	}
	return (EXIT_FAILURE);
}

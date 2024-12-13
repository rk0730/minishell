/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 12:33:15 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include <sys/stat.h>

// ここで終了しない場合は-1を返す　エラーかビルトインの場合は終了ステータスを返す
static int	ft_exec_cmd_h(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe)
{
	if (cmd_info.fd_out == -2 || cmd_info.fd_in == -2)
	{
		ft_close(read_pipe, 17);
		ft_close(write_pipe, 18);
		return (EXIT_FAILURE);
	}
	if (ft_array_len(cmd_info.cmd_argv) == 0)
	{
		ft_close(cmd_info.fd_in, 19);
		ft_close(cmd_info.fd_out, 20);
		ft_close(read_pipe, 21);
		ft_close(write_pipe, 22);
		return (EXIT_SUCCESS);
	}
	//ビルトインの場合はforkせずにここで実行し、終了ステータスを返す
	return (ft_builtin(cmd_info, env_info_p, read_pipe, write_pipe));
}

static void	ft_exec_cmd_parent(t_cmd_info cmd_info, int read_pipe, int write_pipe)
{
	ft_close(cmd_info.fd_out, 23);
	ft_close(cmd_info.fd_in, 24);
	ft_close(read_pipe, 25);
	ft_close(write_pipe, 26);
	//親プロセスはシグナルを無視する
	signal(SIGINT, ft_change_g_signum);
	signal(SIGQUIT, ft_change_g_signum);
}

// コマンドを実行する（execveならfork ビルトインならそのまま）終了ステータスを返す
int	ft_exec_cmd(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe)
{
	int		status;
	pid_t	pid;
	t_env_pair *new_;

	// 環境変数_を更新する
	new_ = (t_env_pair *)malloc(sizeof(t_env_pair));
	new_->key = ft_strdup("_");
	if (ft_array_len(cmd_info.cmd_argv) == 0)
		new_->value = ft_strdup("");
	else
		new_->value = ft_strdup(cmd_info.cmd_argv[ft_array_len(cmd_info.cmd_argv) - 1]);
	new_->next = NULL;
	// builtinの場合はここで実行し、終了ステータスを返す
	status = ft_exec_cmd_h(cmd_info, env_info_p, read_pipe, write_pipe);
	if (status != -1){
		ft_update_env_list(&(env_info_p->env_list), new_, 0);
		return (status);
	}
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0){
		ft_exec_cmd_child(cmd_info, env_info_p, read_pipe, write_pipe);
	}
	else
	{
		ft_exec_cmd_parent(cmd_info, read_pipe, write_pipe);
		waitpid(pid, &status, 0);
		ft_update_env_list(&(env_info_p->env_list), new_, 0);
		return (WEXITSTATUS(status));
	}
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/10/31 14:23:12 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// 相対パスなのでPATHから探して実行する
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

// 絶対パスなのでそのまま実行する
static void	ft_exec_direct(t_cmd_info cmd_info, char **cmd_env)
{
	if (execve(cmd_info.cmd_argv[0], cmd_info.cmd_argv, cmd_env) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0], strerror(errno));
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_info.cmd_argv);
}

// ここで終了しない場合は-1を返す　エラーかビルトインの場合は終了ステータスを返す
static int	ft_exec_cmd_h(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe)
{
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
	return (ft_call_builtin(cmd_info, env_info_p, read_pipe, write_pipe));
}

static void	ft_exec_cmd_child(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe)
{
	char	**path_array;
	char	**cmd_env;

	// pipeに入出力するのか、ファイルに入出力するのかを判断する
	ft_choose_fd(cmd_info, read_pipe, write_pipe, TRUE);
	//シグナルはデフォに戻す
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path_array = ft_gen_path_array(env_info_p->env_list);
	cmd_env = ft_gen_cmd_env(env_info_p->env_list);
	if (ft_strchr(cmd_info.cmd_argv[0], '/') != NULL)
		ft_exec_direct(cmd_info, cmd_env);
	else
		ft_find_and_exec(cmd_info, cmd_env, path_array);
}

static void	ft_exec_cmd_parent(t_cmd_info cmd_info, int read_pipe, int write_pipe)
{
	close(cmd_info.fd_out);
	close(cmd_info.fd_in);
	close(read_pipe);
	close(write_pipe);
	//親プロセスはシグナルを無視する
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
	else if (pid == 0)
		ft_exec_cmd_child(cmd_info, env_info_p, read_pipe, write_pipe);
	else
	{
		ft_exec_cmd_parent(cmd_info, read_pipe, write_pipe);
		waitpid(pid, &status, 0);
		ft_update_env_list(&(env_info_p->env_list), new_, 0);
		return (WEXITSTATUS(status));
	}
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/11 11:06:04 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include <sys/stat.h>

static int ft_is_directory(char *dir)
{
	struct stat statbuf;

    if (access(dir, F_OK) == -1)
        return 0;
    if (stat(dir, &statbuf) == -1) 
		return (0); 
	// YYAMASAK("%s is dir: %d\n", dir, S_ISDIR(statbuf.st_mode));
    return S_ISDIR(statbuf.st_mode);
}

// 絶対パスなのでそのまま実行する
static void	ft_exec_direct(t_cmd_info cmd_info, char **cmd_env)
{

	// YYAMASAK("absolute path: %s\n", cmd_info.cmd_argv[0]);
	if (ft_is_directory(cmd_info.cmd_argv[0]))
	{
		ft_printf_fd(STDERR_FILENO, "%s: Is a directory\n", cmd_info.cmd_argv[0]);
		exit(CMD_EXEC_FAILED);
	}
	if (execve(cmd_info.cmd_argv[0], cmd_info.cmd_argv, cmd_env) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0], strerror(errno));
		if (errno == ENOENT) 
			exit(CMD_NOT_FOUND);
		else if (errno == EACCES)
			exit(CMD_EXEC_FAILED);
		YYAMASAK("relative_path: %d\n", errno);
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_info.cmd_argv);
}

// 相対パスなのでPATHから探して実行する
static void	ft_find_and_exec(t_cmd_info cmd_info, char **cmd_env, char **path_array, t_env_info *env_info_p)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	if (!path_array[i])
		ft_exec_direct(cmd_info, cmd_env);
	while (path_array[i])
	{
		tmp = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_info.cmd_argv[0]);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, cmd_info.cmd_argv, cmd_env) == -1)
			{
				ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0], strerror(errno));
				YYAMASAK("relative_path: %d\n", errno);
				exit(CMD_ERROR);
			}
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd_info.cmd_argv[0]);
	ft_free_array(cmd_info.cmd_argv);
	exit(CMD_NOT_FOUND);
}

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
	signal(SIGPIPE, SIG_DFL);
	path_array = ft_gen_path_array(env_info_p->env_list);
	cmd_env = ft_gen_cmd_env(env_info_p->env_list);
	if (ft_strchr(cmd_info.cmd_argv[0], '/') != NULL)
		ft_exec_direct(cmd_info, cmd_env);
	else
		ft_find_and_exec(cmd_info, cmd_env, path_array, env_info_p);
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
		ft_close(env_info_p->std_in, 29);
		ft_close(env_info_p->std_out, 30);
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

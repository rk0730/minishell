/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/25 21:02:34 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	ft_find_and_exec(t_cmd_info cmd_info, char **path_array)
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
			if (execve(cmd_path, cmd_info.cmd_argv, NULL) == -1)
				exit(CMD_ERROR);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd_info.cmd_argv[0]);
	ft_free_array(cmd_info.cmd_argv);
	exit(CMD_NOT_FOUND);
}

static void	ft_exec_direct(t_cmd_info cmd_info)
{
	// if (cmd_info.fd_out != -1)
	// 	dup2(cmd_info.fd_out, STDOUT_FILENO);
	// if (cmd_info.fd_in != 1)
	// 	dup2(cmd_info.fd_in, STDIN_FILENO);
	if (execve(cmd_info.cmd_argv[0], cmd_info.cmd_argv, NULL) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_argv[0], strerror(errno));
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_info.cmd_argv);
}

// コマンドを実行する（execveならfork ビルトインならそのまま）終了ステータスを返す
int	ft_exec_cmd(t_cmd_info cmd_info,t_env_info env_info, int read_pipe, int write_pipe)
{
	char	**path_array;
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
		return (EXIT_FAILURE);
	if (ft_array_len(cmd_info.cmd_argv) == 0)
	{
		close(cmd_info.fd_in);
		close(cmd_info.fd_out);
		close(read_pipe);
		close(write_pipe);
		return (0);
	}
	// pipeに入出力するのか、ファイルに入出力するのかを判断する
	if (cmd_info.fd_in != -1)
	{
		close(read_pipe);
		dup2(cmd_info.fd_in, STDIN_FILENO);
		close(cmd_info.fd_in);
	} else if (read_pipe != -1)
	{
		dup2(read_pipe, STDIN_FILENO);
		close(read_pipe);
	}
	if (cmd_info.fd_out != -1)
	{
		close(write_pipe);
		dup2(cmd_info.fd_out, STDOUT_FILENO);
		close(cmd_info.fd_out);
	} else if (write_pipe != -1)
	{
		dup2(write_pipe, STDOUT_FILENO);
		close(write_pipe);
	}
	//ビルトインの場合はforkせずにここで実行し、終了ステータスを返す
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		path_array = ft_gen_path_array(env_info.env_list);
		if (ft_strchr(cmd_info.cmd_argv[0], '/') != NULL)
			ft_exec_direct(cmd_info);
		else
			ft_find_and_exec(cmd_info, path_array);
	}
	else
	{
		// close(cmd_info.fd_out);
		// close(cmd_info.fd_in);
		// close(read_pipe);
		// close(write_pipe);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (EXIT_FAILURE);
}

// コマンドを実行する関数、これを呼んだプロセスはexitされる
// void	ft_exec_cmd(char *cmd, t_env_info env_info)
// {
// 	char		**tokens;
// 	char		**path_array;
// 	t_cmd_info	cmd_info;

// 	char **cmds = ft_gen_cmds(cmd);
// 	ft_show_all(cmds);
// 	tokens = ft_gen_tokens(cmd);
// 	if (tokens == NULL)//クォーテーションの文法エラー
// 	{
// 		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
// 		exit(SYNTAX_ERROR);
// 	}
// 	// tokensからfdのエラーをチェックする
// 	if (ft_redirect_err(tokens) == 1)
// 	{
// 		//ヒアドクはここでやる必要あり
// 		cmd_info.fd_in = ft_heredoc(tokens, env_info);
// 		ft_free_array(tokens);
// 		exit(SYNTAX_ERROR);
// 	}
// 	//cmd_argv out_fd in_fdなどの情報をtokenから持ってくる
// 	//まずヒアドク、最後がリダイレクト記号の場合はエラー処理、次にinfile outfileを同時に頭から順に実行する
// 	cmd_info.fd_in = ft_heredoc(tokens, env_info);
// 	// 最後の文字がリダイレクト記号だった場合のエラー処理
// 	if (ft_is_last_redirect(tokens) == 1)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
// 		ft_free_array(tokens);
// 		exit(SYNTAX_ERROR);
// 	}
// 	// cmd_info.fd_out = ft_out_fd(tokens, env_list);
// 	ft_in_out_fd(tokens, env_info, &cmd_info, cmd_info.fd_in);
// 	cmd_info.cmd_argv = ft_gen_cmd_argv(tokens, env_info);
// 	ft_free_array(tokens);
// 	if (cmd_info.fd_out == -2 || cmd_info.fd_in == -2)
// 	{
// 		ft_free_array(cmd_info.cmd_argv);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (ft_array_len(cmd_info.cmd_argv) == 0)
// 	{
// 		close(cmd_info.fd_out);
// 		close(cmd_info.fd_in);
// 		ft_free_array(cmd_info.cmd_argv);
// 		exit(EXIT_SUCCESS);
// 	}
// 	path_array = ft_gen_path_array(env_info.env_list);
// 	if (ft_strchr(cmd_info.cmd_argv[0], '/') != NULL)
// 		ft_exec_direct(cmd_info);
// 	else
// 		ft_find_and_exec(cmd_info, path_array);
// }

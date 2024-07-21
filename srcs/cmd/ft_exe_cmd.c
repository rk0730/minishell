/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:05:08 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/21 20:00:10 by kitaoryoma       ###   ########.fr       */
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
		cmd_path = ft_strjoin(tmp, cmd_info.cmd_array[0]);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			if (cmd_info.fd_out != -1)
				dup2(cmd_info.fd_out, STDOUT_FILENO);
			if (cmd_info.fd_in != 1)
				dup2(cmd_info.fd_in, STDIN_FILENO);
			if (execve(cmd_path, cmd_info.cmd_array, NULL) == -1)
				exit(CMD_ERROR);
		}
		free(cmd_path);
		i++;
	}
	ft_printf_fd(STDERR_FILENO, "%s: command not found\n", cmd_info.cmd_array[0]);
	ft_free_array(cmd_info.cmd_array);
	exit(CMD_NOT_FOUND);
}

static void	ft_exec_direct(t_cmd_info cmd_info)
{
	if (cmd_info.fd_out != -1)
		dup2(cmd_info.fd_out, STDOUT_FILENO);
	if (cmd_info.fd_in != 1)
		dup2(cmd_info.fd_in, STDIN_FILENO);
	if (execve(cmd_info.cmd_array[0], cmd_info.cmd_array, NULL) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", cmd_info.cmd_array[0], strerror(errno));
		exit(CMD_ERROR);
	}
	ft_free_array(cmd_info.cmd_array);
}

// コマンドを実行する関数、これを呼んだプロセスはexitされる
void	ft_exec_cmd(char *cmd, t_env_pair *env_list)
{
	char	**tokens;
	char	**path_array;
	t_cmd_info	cmd_info;
	
	// cmd_array = ft_gen_tokens(cmd);//ft_gen_cmd_array()に変える！
	
	tokens = ft_gen_tokens(cmd);
	if (tokens == NULL)//クォーテーションの文法エラー
	{
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
		exit(SYNTAX_ERROR);
	}
	// tokensからfdのエラーをチェックする
	if (ft_fd_error(tokens) == 1)
	{
		//ヒアドクはここでやる必要あり
		cmd_info.fd_in = ft_heredoc(tokens, env_list);
		ft_free_array(tokens);
		exit(SYNTAX_ERROR);
	}
	//cmd_array out_fd in_fdなどの情報をtokenから持ってくる
	//まずヒアドク、最後がリダイレクト記号の場合はエラー処理、次にinfile outfileを同時に頭から順に実行する
	cmd_info.fd_in = ft_heredoc(tokens, env_list);
	// 最後の文字がリダイレクト記号だった場合のエラー処理
	if (ft_is_last_redirect(tokens) == 1)
	{
		ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
		ft_free_array(tokens);
		exit(SYNTAX_ERROR);
	}
	// cmd_info.fd_out = ft_out_fd(tokens, env_list);
	ft_in_out_fd(tokens, env_list, &cmd_info, cmd_info.fd_in);
	cmd_info.cmd_array = ft_gen_cmd_array(tokens, env_list);
	ft_free_array(tokens);
	if (cmd_info.fd_out == -2 || cmd_info.fd_in == -2)
	{
		ft_free_array(cmd_info.cmd_array);
		exit(EXIT_FAILURE);
	}
	if (ft_array_len(cmd_info.cmd_array) == 0)
	{
		close(cmd_info.fd_out);
		close(cmd_info.fd_in);
		ft_free_array(cmd_info.cmd_array);
		exit(EXIT_SUCCESS);
	}
	path_array = ft_gen_path_array(env_list);
	if (ft_strchr(cmd_info.cmd_array[0], '/') != NULL)
		ft_exec_direct(cmd_info);
	else
		ft_find_and_exec(cmd_info, path_array);
}

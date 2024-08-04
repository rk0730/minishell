/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:39:02 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/08/04 23:06:26 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// 入力リダイレクト処理　文法エラー処理はここではしない。エラーがあった場合は-2を返す
static int	ft_in_fd(char **tokens, t_env_info env_info, int i)
{
	int		result;
	char	*file;

	file = ft_tokenize(tokens[i + 1], env_info);
	if (file == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", tokens[i + 1]);
		return (-2);
	}
	result = open(file, O_RDONLY);
	if (result == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", file, strerror(errno));
		free(file);
		return (-2);
	}
	free(file);
	return (result);
}

// tokens[i]が">>"か">"かを判定して、その後のファイル名を開いて、そのfdを返す
// 出力、追記リダイレクト処理　文法エラー処理はここではしない。エラーがあった場合は-2を返す
static int	ft_out_fd(char **tokens, t_env_info env_info, int i)
{
	int		result;
	char	*file;

	file = ft_tokenize(tokens[i + 1], env_info);
	if (file == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "%s: ambiguous redirect\n", tokens[i + 1]);
		return (-2);
	}
	if (ft_strncmp(tokens[i], ">", 2) == 0)
	{
		result = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (ft_strncmp(tokens[i], ">>", 3) == 0)
		result = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	// else
	// {
	// 	result = -1;
	// 	printf("error in ft_out_fd\n");
	// }
	if (result == -1)
	{
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", file, strerror(errno));
		free(file);
		return (-2);
	}
	free(file);
	return (result);
}

// エラーなら1を返す
static int	ft_in_out_fd_h(char **tokens, t_env_info env_info, t_cmd_info *cmd_info, int i)
{
	if (tokens[i][0] == '>')
	{
		if (cmd_info->fd_out != -1)
			close(cmd_info->fd_out);
		cmd_info->fd_out = ft_out_fd(tokens, env_info, i);
		if (cmd_info->fd_out == -2)
			return (1);
	}
	return (0);
}

// エラーがあった場合は-2を返す（権限、ambiguous redirectなど）
// リダイレクト先がない場合は-1を返す
// cmd_infoの入力リダイレクト、出力リダイレクトのfdを入れる　ヒアドクはすでに処理が完了している前提
void	ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info, int heredoc_fd)
{
	int	i;

	i = 0;
	cmd_info->fd_in = -1;
	cmd_info->fd_out = -1;
	while (tokens[i])
	{
		if (ft_in_out_fd_h(tokens, env_info, cmd_info, i) == 1)
			return ;
		else if (ft_strncmp(tokens[i], "<", 2) == 0)
		{
			if (cmd_info->fd_in != -1 && cmd_info->fd_in != heredoc_fd)
				close(cmd_info->fd_in);
			cmd_info->fd_in = ft_in_fd(tokens, env_info, i);
			if (cmd_info->fd_in == -2)
				return ;
		}
		else if (ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			if (cmd_info->fd_in != -1 && cmd_info->fd_in != heredoc_fd)
				close(cmd_info->fd_in);
			cmd_info->fd_in = heredoc_fd;
		}
		i++;
	}
}

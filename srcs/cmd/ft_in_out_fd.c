/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:39:02 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/07/21 23:20:30 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

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
		if (tokens[i][0] == '>')
		{
			if (cmd_info->fd_out != -1)
				close(cmd_info->fd_out);
			cmd_info->fd_out = ft_out_fd(tokens, env_info, i);
			if (cmd_info->fd_out == -2)
				return ;
		}
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

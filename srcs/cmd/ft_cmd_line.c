/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:13:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/28 14:22:15 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// コマンドを実行し、終了ステータスを返す
int	ft_exec_cmdline(char *input, t_env_info env_info)
{
	char		**cmds;
	t_cmd_info	*cmd_list;
	int			last_index;
	int			std_in;
	int			std_out;
	int			status;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	cmds = ft_gen_cmds(input);
	if (!cmds)
		return (SYNTAX_ERROR);
	cmd_list = ft_cmd_info_list(cmds, env_info);
	if (!cmd_list)
	{
		ft_free_array(cmds);
		return (SYNTAX_ERROR);
	}
	last_index = ft_array_len(cmds) - 1;
	status = ft_exec_pipe(cmd_list, env_info, last_index);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
	ft_free_array(cmds);
	free(cmd_list);
	return (status);
}

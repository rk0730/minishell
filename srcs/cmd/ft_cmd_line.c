/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:13:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/31 10:51:41 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

// コマンドを実行し、終了ステータスを返す
int	ft_exec_cmdline(t_env_info *env_info_p)
{
	char		**cmds;
	t_cmd_info	*cmd_list;
	int			last_index;
	int			std_in;
	int			std_out;
	int			status;
	char		*input_cmd;
	char		*tmp;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	input_cmd = get_next_line(env_info_p->input_fd);
	tmp = input_cmd;
	input_cmd = ft_strtrim(tmp, "\n");
	free(tmp);
	cmds = ft_gen_cmds(input_cmd);
	if (!cmds)
		return (SYNTAX_ERROR);
	cmd_list = ft_cmd_info_list(cmds, env_info_p);
	if (!cmd_list)
	{
		ft_free_array(cmds);
		dup2(std_in, STDIN_FILENO);
		dup2(std_out, STDOUT_FILENO);
		close(std_in);
		close(std_out);
		close(env_info_p->input_fd);
		if (g_signum == SIGINT)
			return (SIGINT_ERROR);
		return (SYNTAX_ERROR);
	}
	last_index = ft_array_len(cmds) - 1;
	status = ft_exec_cmd_list(cmd_list, *env_info_p, last_index);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	close(std_in);
	close(std_out);
	ft_free_array(cmds);
	free(cmd_list);
	close(env_info_p->input_fd);
	return (status);
}

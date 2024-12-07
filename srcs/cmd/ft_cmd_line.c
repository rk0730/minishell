/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:13:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/06 17:20:12 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	**ft_help(t_env_info *env_info_p)
{
	char	*input_cmd;
	char	*tmp;
	char	**cmds;

	// 入力の１行目がコマンド
	input_cmd = get_next_line(env_info_p->input_fd);
	tmp = input_cmd;
	input_cmd = ft_strtrim(tmp, "\n");
	free(tmp);
	// コマンドを|で分割
	cmds = ft_gen_cmds(input_cmd);
	free(input_cmd);
	return (cmds);
}

static int	ft_help2(char **cmds, t_cmd_info *cmd_list, t_env_info *env_info_p)
{
	int	last_index;
	int	status;
	int	i;

	// コマンドを実行する
	// YYAMASAK("ft_help2\n");
	last_index = ft_array_len(cmds) - 1;
	status = ft_exec_cmd_list(cmd_list, env_info_p, last_index);
	i = 0;
	while (i <= last_index)
	{
		ft_free_array(cmd_list[i].cmd_argv);
		i++;
	}
	free(cmd_list);
	return (status);
}

// static void	ft_clean(char **cmds, t_env_info *env_info_p)
// {
// 	ft_free_array(cmds);
// 	ft_close(env_info_p->input_fd, 10);
// }


// コマンドを実行し、終了ステータスを返す
int	ft_exec_cmdline(t_env_info *env_info_p)
{
	char		**cmds;
	t_cmd_info	*cmd_list;
	int			status;

	cmds = ft_help(env_info_p);
	if (!cmds)
	{
		ft_close(env_info_p->input_fd, 9);
		return (SYNTAX_ERROR);
	}
	env_info_p->std_in = dup(STDIN_FILENO);
	env_info_p->std_out = dup(STDOUT_FILENO);
	//　各コマンドのリダイレクトや環境変数展開などを実行する
	cmd_list = ft_cmd_info_list(cmds, env_info_p);
	ft_close(env_info_p->input_fd, 10);
	if (!cmd_list)
	{
		// ft_clean(cmds, env_info_p);
		dup2(env_info_p->std_in, STDIN_FILENO);
		dup2(env_info_p->std_out, STDOUT_FILENO);
		ft_close(env_info_p->std_in, 11);
		ft_close(env_info_p->std_out, 12);
		ft_free_array(cmds);
		if (g_signum == SIGINT)
			return (SIGINT_ERROR);
		return (SYNTAX_ERROR);
	}
	// コマンドを実行する
	status = ft_help2(cmds, cmd_list, env_info_p);
	// 掃除
	// ft_clean(cmds, env_info_p);
	dup2(env_info_p->std_in, STDIN_FILENO);
	dup2(env_info_p->std_out, STDOUT_FILENO);
	ft_close(env_info_p->std_in, 13);
	ft_close(env_info_p->std_out, 14);
	ft_free_array(cmds);
	ft_close(env_info_p->input_fd, 15);
	return (status);
}

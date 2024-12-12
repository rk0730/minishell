/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:13:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/12 19:17:17 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	**ft_help(t_env_info *env_info_p)
{
	char	**cmds;

	// コマンドを|で分割
	cmds = ft_gen_cmds(env_info_p->input);
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
		return (SYNTAX_ERROR);
	}
	//　各コマンドのリダイレクトや環境変数展開などを実行する
	cmd_list = ft_cmd_info_list(cmds, env_info_p);
	if (!cmd_list)
	{
		// ft_clean(cmds, env_info_p);
		ft_free_array(cmds);
		if (g_signum == SIGINT)
			return (SIGINT_ERROR);
		return (SYNTAX_ERROR);
	}
	// コマンドを実行する
	status = ft_help2(cmds, cmd_list, env_info_p);
	// 掃除
	// ft_clean(cmds, env_info_p);
	ft_free_array(cmds);
	return (status);
}

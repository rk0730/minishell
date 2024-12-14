/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:13:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 13:18:08 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static int	ft_help(char **cmds, t_cmd_info *cmd_list, t_env_info *env_info_p)
{
	int	last_index;
	int	status;
	int	i;

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

int	ft_exec_cmdline(t_env_info *env_info_p)
{
	char		**cmds;
	t_cmd_info	*cmd_list;
	int			status;

	cmds = ft_gen_cmds(env_info_p->input);
	if (!cmds)
		return (SYNTAX_ERROR);
	cmd_list = ft_cmd_info_list(cmds, env_info_p);
	if (!cmd_list)
	{
		ft_free_array(cmds);
		if (g_signum == SIGINT)
			return (SIGINT_ERROR);
		return (SYNTAX_ERROR);
	}
	status = ft_help(cmds, cmd_list, env_info_p);
	ft_free_array(cmds);
	return (status);
}

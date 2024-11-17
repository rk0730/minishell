/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:55:05 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/17 19:32:34 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include "builtins.h"

int			ft_exec_cmdline(t_env_info *env_info_p);
int			ft_exec_cmd(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe);
int			ft_exec_cmd_list(t_cmd_info *cmd_list, t_env_info *env_info_p, int last_index);
void		ft_sigint_cmd(int sig);
void		ft_sigquit_cmd(int sig);
void		ft_change_g_signum(int sig);

#endif
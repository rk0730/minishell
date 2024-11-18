/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:01:23 by rkitao            #+#    #+#             */
/*   Updated: 2024/11/17 18:40:10 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "pre_cmd.h"

enum e_cmd_error
{
	CMD_ERROR = 1,
	CMD_NOT_FOUND = 127,
	SYNTAX_ERROR = 2,
	SIGINT_ERROR = 130,
	SIGQUIT_ERROR = 131,
};


void	ft_choose_fd(t_cmd_info cmd_info, int read_pipe, int write_pipe, t_bool need_input);
int		ft_call_builtin(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe);
int		ft_echo(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_cd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_pwd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_env(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_exit(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_export(t_cmd_info cmd_info, t_env_info env_info,  int read_pipe, int write_pipe);
void	ft_update_env_list(t_env_pair **env_list_p, t_env_pair *new, int mode);
int 	ft_unset(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe);
#endif
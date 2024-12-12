/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:01:23 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/12 18:05:21 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "pre_cmd.h"

enum e_cmd_error
{
	CMD_ERROR = 1,
	CMD_NOT_FOUND = 127,
	CMD_EXEC_FAILED = 126,
	SYNTAX_ERROR = 2,
	SIGINT_ERROR = 130,
	SIGQUIT_ERROR = 131,
};


void	ft_choose_fd(t_cmd_info cmd_info, int read_pipe, int write_pipe, t_bool need_input);
int		ft_builtin(t_cmd_info cmd_info, t_env_info *env_info_p, int read_pipe, int write_pipe);
int		ft_echo(t_cmd_info cmd_info, t_env_info env_info);
int		ft_cd(t_cmd_info cmd_info, t_env_info env_info);
int		ft_pwd(t_cmd_info cmd_info, t_env_info env_info);
int		ft_env(t_cmd_info cmd_info, t_env_info env_info);
int		ft_exit(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_export(t_cmd_info cmd_info, t_env_info env_info);
int 	ft_unset(t_cmd_info cmd_info, t_env_info *env_info_p);
char 	*ft_internal_pwd(int mode);
t_env_pair	*ft_new_env2(char *key, char *value);
#endif
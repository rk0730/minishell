/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:01:23 by rkitao            #+#    #+#             */
/*   Updated: 2024/08/02 17:51:35 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

enum e_cmd_error
{
	CMD_ERROR = 1,
	CMD_NOT_FOUND = 127,
	SYNTAX_ERROR = 2,
	SIGINT_ERROR = 130,
	SIGQUIT_ERROR = 131,
};

typedef enum e_token_status
{
	NORMAL,
	SINGLE_QUOTE,//'が足りない
	DOUBLE_QUOTE,//"が足りない
	// REDIRECT,// >>>や<<<,<>など不適なリダイレクト
}	t_token_status;

typedef struct s_cmd_info
{
	char	**cmd_argv;
	int		fd_in;
	int		fd_out;
}	t_cmd_info;	


void	ft_choose_fd(t_cmd_info cmd_info, int read_pipe, int write_pipe);
int		ft_call_builtin(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_cd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_pwd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);
int		ft_exit(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe);

#endif
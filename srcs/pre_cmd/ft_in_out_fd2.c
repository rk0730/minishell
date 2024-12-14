/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_fd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:56:36 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/14 18:49:45 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"

static int	_ft_help3(char **tokens, t_env_info env_info, t_cmd_info *cmd_info,
		t_param2 *param)
{
	(void)env_info;
	if (ft_strncmp(tokens[param->i], "<<", 3) == 0)
	{
		if (cmd_info->fd_in != -1 && cmd_info->fd_in != param->heredoc_fd)
			ft_close(cmd_info->fd_in, 38);
		cmd_info->fd_in = param->heredoc_fd;
		return (2);
	}
	return (0);
}

static int	_ft_help2(char **tokens, t_env_info env_info, t_cmd_info *cmd_info,
		t_param2 *param)
{
	if (ft_strncmp(tokens[param->i], "<", 2) == 0)
	{
		if (cmd_info->fd_in != -1 && cmd_info->fd_in != param->heredoc_fd)
			ft_close(cmd_info->fd_in, 37);
		cmd_info->fd_in = _ft_in_fd(tokens, cmd_info, env_info, param->i);
		if (cmd_info->fd_in == -2)
		{
			param->is_err = TRUE;
			return (1);
		}
		return (2);
	}
	return (0);
}

static int	_ft_help1(char **tokens, t_env_info env_info, t_cmd_info *cmd_info,
		t_param2 *param)
{
	if (tokens[param->i][0] == '>')
	{
		ft_close(cmd_info->fd_out, 36);
		cmd_info->fd_out = _ft_out_fd(tokens, env_info, param->i);
		if (cmd_info->fd_out == -2)
		{
			param->is_err = TRUE;
			return (1);
		}
		return (2);
	}
	return (0);
}

static int	_ft_help_all(char **tokens, t_env_info env_info,
		t_cmd_info *cmd_info, t_param2 *param)
{
	int	tmp;

	tmp = _ft_help1(tokens, env_info, cmd_info, param);
	if (tmp >= 1)
		return (tmp);
	tmp = _ft_help2(tokens, env_info, cmd_info, param);
	if (tmp >= 1)
		return (tmp);
	tmp = _ft_help3(tokens, env_info, cmd_info, param);
	return (tmp);
}

void	_ft_in_out_fd(char **tokens, t_env_info env_info, t_cmd_info *cmd_info,
		int heredoc_fd)
{
	t_param2	param;
	int			tmp;

	param.is_err = FALSE;
	param.i = 0;
	param.heredoc_fd = heredoc_fd;
	cmd_info->fd_in = -1;
	cmd_info->fd_out = -1;
	while (tokens[param.i])
	{
		tmp = _ft_help_all(tokens, env_info, cmd_info, &param);
		if (tmp == 1)
			break ;
		param.i++;
	}
	if (cmd_info->fd_in != heredoc_fd)
		ft_close(heredoc_fd, 39);
	if (param.is_err == TRUE)
	{
		ft_close(cmd_info->fd_in, 40);
		ft_close(cmd_info->fd_out, 41);
		cmd_info->fd_in = -2;
		cmd_info->fd_out = -2;
	}
}

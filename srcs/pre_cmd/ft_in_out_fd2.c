/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_fd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:56:36 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/14 18:13:41 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pre_cmd_private.h"


void	_ft_in_out_fd(char **tokens, t_env_info env_info,
		t_cmd_info *cmd_info, int heredoc_fd)
{
	int		i;
	t_bool	is_err;

	is_err = FALSE;
	i = 0;
	cmd_info->fd_in = -1;
	cmd_info->fd_out = -1;
	while (tokens[i])
	{
		// ft_in_out_fd_h(tokens, env_info, cmd_info, i) == 1);
		if (tokens[i][0] == '>')
		{
			ft_close(cmd_info->fd_out, 36);
			cmd_info->fd_out = _ft_out_fd(tokens, env_info, i);
			if (cmd_info->fd_out == -2)
			{
				is_err = TRUE;
				break ;
			}
		}
		else if (ft_strncmp(tokens[i], "<", 2) == 0)
		{
			if (cmd_info->fd_in != -1 && cmd_info->fd_in != heredoc_fd)
				ft_close(cmd_info->fd_in, 37);
			cmd_info->fd_in = _ft_in_fd(tokens, cmd_info, env_info, i);
			if (cmd_info->fd_in == -2)
			{
				is_err = TRUE;
				break ;
			}
		}
		else if (ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			if (cmd_info->fd_in != -1 && cmd_info->fd_in != heredoc_fd)
				ft_close(cmd_info->fd_in, 38);
			cmd_info->fd_in = heredoc_fd;
		}
		i++;
	}
	if (cmd_info->fd_in != heredoc_fd)
		ft_close(heredoc_fd, 39);
	if (is_err == TRUE)
	{
		ft_close(cmd_info->fd_in, 40);
		ft_close(cmd_info->fd_out, 41);
		cmd_info->fd_in = -2;
		cmd_info->fd_out = -2;
	}
}
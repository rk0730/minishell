/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:27:26 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/07 16:14:24 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"


char *ft_internal_ped

int	ft_pwd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	char	pathname[PATH_MAX];

	(void)env_info;
	ft_choose_fd(cmd_info, read_pipe, write_pipe, FALSE);
	getcwd(pathname, PATH_MAX);
	// printf("%s\n", pathname);
	return (0);
}
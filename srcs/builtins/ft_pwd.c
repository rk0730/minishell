/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:27:26 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/07 17:11:50 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"


char *ft_internal_pwd(int mode)
{
	static char pathname[PATH_MAX];

	if (mode)
	{
		getcwd(pathname, PATH_MAX);
	}
	return (pathname);
}

int	ft_pwd(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	(void)env_info;
	ft_choose_fd(cmd_info, read_pipe, write_pipe, FALSE);
	printf("%s\n", ft_internal_pwd(0));
	return (0);
}

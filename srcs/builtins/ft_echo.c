/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:29:34 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:56:22 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_is_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(t_cmd_info cmd_info, t_env_info env_info)
{
	int	n_option;
	int	i;

	(void)env_info;
	i = 1;
	while (ft_is_option(cmd_info.cmd_argv[i]))
		i++;
	if (i == 1)
		n_option = 0;
	else
		n_option = 1;
	while (cmd_info.cmd_argv[i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s", cmd_info.cmd_argv[i]);
		if (cmd_info.cmd_argv[i + 1])
			ft_printf_fd(STDOUT_FILENO, " ");
		i++;
	}
	if (!n_option)
		ft_printf_fd(STDOUT_FILENO, "\n");
	return (0);
}

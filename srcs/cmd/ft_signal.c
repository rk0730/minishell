/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:21:48 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 15:21:29 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

//コマンド実行中SIGINTの処理
void	ft_sigint_cmd(int sig)
{
	g_signum = sig;
	ft_printf_fd(STDOUT_FILENO, "\n");
}

//コマンド実行中SIGQUITの処理
void	ft_sigquit_cmd(int sig)
{
	g_signum = sig;
	ft_printf_fd(STDOUT_FILENO, "Quit (core dumped)\n");
}

void	ft_change_g_signum(int sig)
{
	g_signum = sig;
}

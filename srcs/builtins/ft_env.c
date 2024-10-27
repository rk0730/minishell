/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:38:14 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/08/04 23:57:08 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_cmd_info cmd_info, t_env_info env_info, int read_pipe, int write_pipe)
{
	ft_choose_fd(cmd_info, read_pipe, write_pipe);
	ft_show_env_list(env_info.env_list);
	return (0);
}

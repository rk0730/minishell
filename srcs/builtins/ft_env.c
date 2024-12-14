/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:38:14 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 14:50:24 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_cmd_info cmd_info, t_env_info env_info)
{
	(void)cmd_info;
	ft_show_env_list(env_info.env_list);
	return (0);
}

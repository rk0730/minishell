/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:39:55 by yyamasak          #+#    #+#             */
/*   Updated: 2024/12/13 12:46:35 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "cmd.h"
#include "env.h"

void	ft_show_env_list(t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
		{
			if (strncmp(tmp->key, "_", 2) == 0)
				ft_printf_fd(STDOUT_FILENO, "%s=%s\n", tmp->key,
					"/usr/bin/env");
			else
				ft_printf_fd(STDOUT_FILENO, "%s=%s\n", tmp->key, tmp->value);
		}
		tmp = tmp->next;
	}
}

void	ft_show_env_list2(t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		// if (ft_strncmp(tmp->key, "_", 2) == 0 || ft_strncmp(tmp->key, "PATH",
		// 		5) == 0)
		if (ft_strncmp(tmp->key, "_", 2) == 0)
			(void)env_list;
		else if (tmp->value)
			ft_printf_fd(1, "declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			ft_printf_fd(1, "declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

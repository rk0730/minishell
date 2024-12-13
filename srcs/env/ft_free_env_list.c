/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:38:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 12:39:19 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	ft_free_env_list(t_env_pair *env_list)
{
	t_env_pair	*node;
	
	node = env_list;
	if (!env_list)
		return ;
	while (env_list)
	{
		node = env_list->next;
		if (env_list->key)
		{
			free(env_list->key);
			env_list->key = NULL;
		}
		if (env_list->value)
		{
			free(env_list->value);
			env_list->value = NULL;
		}
		free(env_list);
		env_list = node;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:42:33 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/13 12:45:35 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_pair	*ft_search_env_node(char *search, t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, search, ft_strlen(tmp->key) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// searchという環境変数が見つかったらそのvalueを返す
char	*ft_search_env(char *search, t_env_pair *env_list)
{
	t_env_pair	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, search, ft_strlen(tmp->key) + 1) == 0)
		{
			if (tmp->value)
				return (ft_strdup(tmp->value));
			else
				break ;
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

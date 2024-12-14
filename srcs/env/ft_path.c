/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyamasak <yyamasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/14 13:27:20 by yyamasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_gen_path_array(t_env_pair *env_list)
{
	t_env_pair	*tmp;
	char		**path_array;
	char		*path;

	tmp = NULL;
	if (env_list != NULL)
		tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 5) == 0)
		{
			path = tmp->value;
			path_array = ft_split(path, ':');
			return (path_array);
		}
		tmp = tmp->next;
	}
	path_array = (char **)malloc(sizeof(char *) * 1);
	path_array[0] = NULL;
	return (path_array);
}

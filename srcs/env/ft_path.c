/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/07 18:14:26 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_gen_path_array(t_env_pair **env_list)
{
	t_env_pair	*tmp;
	char		**path_array;
	char		*path;

	tmp = *env_list;
	while (tmp)
	{
		printf("now %s %s\n", tmp->key, tmp->value);
		if (ft_strlen(tmp->key) == 4 && ft_strncmp(tmp->key, "PATH", 4) == 0)
		{
			printf("found PATH\n");
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

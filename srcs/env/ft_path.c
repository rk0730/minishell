/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:59:39 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/20 20:51:37 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_gen_path_array(t_env_pair *env_list)
{
	t_env_pair	*tmp;
	char		**path_array;
	char		*path;

	// to do: 環境変数ごとdelete?されたときは、env_listがnullになるためif文を追加
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
	ft_show_all(path_array);
	return (path_array);
}

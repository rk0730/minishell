/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gen_cmd_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:07:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/14 18:23:57 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**ft_gen_cmd_env(t_env_pair *env_list)
{
	char		**cmd_env;
	t_env_pair	*tmp;
	char		*env_str;
	char		*tmp_str;

	cmd_env = (char **)malloc(sizeof(char *));
	if (!cmd_env)
		return (NULL);
	cmd_env[0] = NULL;
	tmp = env_list;
	while (tmp)
	{
		tmp_str = ft_strdup(tmp->key);
		env_str = ft_strjoin(tmp_str, "=");
		free(tmp_str);
		tmp_str = env_str;
		env_str = ft_strjoin(tmp_str, tmp->value);
		free(tmp_str);
		cmd_env = ft_add_str(cmd_env, env_str);
		tmp = tmp->next;
	}
	return (cmd_env);
}

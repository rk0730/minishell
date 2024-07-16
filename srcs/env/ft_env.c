/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:18:19 by rkitao            #+#    #+#             */
/*   Updated: 2024/07/16 17:15:22 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

// 新しい環境変数を作成する
// envには"USER=rkitao"のような文字列が入る
t_env_pair	*ft_new_env(char *env)
{
	t_env_pair	*env_pair;

	env_pair = (t_env_pair *)malloc(sizeof(t_env_pair));
	if (!env_pair)
		return (NULL);
	env_pair->key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	env_pair->value = ft_substr(env, ft_strchr(env, '=') - env + 1, env + ft_strlen(env) - ft_strchr(env, '=') - 1);
	env_pair->next = NULL;
	return (env_pair);
}

void	ft_add_env_list(t_env_pair **env_list, char *env)
{
	t_env_pair	*new_env;
	t_env_pair	*tmp;

	new_env = ft_new_env(env);
	if (!*env_list)
		exit(EXIT_FAILURE);
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}

t_env_pair	**ft_gen_env_list(char **envp)
{
	t_env_pair	**env_list;
	t_env_pair	*first;
	size_t		i;

	first = ft_new_env(envp[0]);
	i = 1;
	while (envp[i])
	{
		// printf("first %s %s\n", first->key, first->value);
		ft_add_env_list(&first, envp[i]);
		i++;
	}
	env_list = &first;
	// printf("first %s %s\n", first->key, first->value);
	return (env_list);
}

void	ft_show_env_list(t_env_pair **env_list)
{
	t_env_pair	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		printf("%s==%s\n", tmp->key, tmp->value);
		// なぜかここでtmpのkey,valueを表示すると*env_listのアドレスが変わる
		// printf("%p\n", *env_list);
		tmp = tmp->next;
	}
}
